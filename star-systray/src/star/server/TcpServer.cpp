#include "includes/star/Star.hpp"


star::server::TcpServer::TcpServer() {}

star::server::TcpServer::~TcpServer() {}

void star::server::TcpServer::initServer()
{
    this->_pServer = new QTcpServer(this);

    // Whenever a user connects, it will emit signal
    connect(this->_pServer, &QTcpServer::newConnection,
            this, &TcpServer::onNewConnection);

    if(this->_pServer->listen(QHostAddress::LocalHost, 38585)) {
        qInfo() << Q_FUNC_INFO << ": Started Star tray icon local TCP server.";
    } else {
        qWarning() << Q_FUNC_INFO << ": Failed to start Star tray icon local TCP server. App may malfunction.";
    }
}

void star::server::TcpServer::closeAllClients()
{
    QList<QTcpSocket *>::iterator i;

    for (i = this->_lstSocketClients.begin(); i != this->_lstSocketClients.end(); ++i) {
        auto socketClient = *i;
        socketClient->close();
        socketClient->deleteLater();
    }

}

void star::server::TcpServer::close()
{
    if(this->_pServer) {
        this->_pServer->close();
    }
}

void star::server::TcpServer::onNewConnection()
{
    // When new connection arrived, we will keep it in our collection
    auto clientSocket = this->_pServer->nextPendingConnection();

    this->_lstSocketClients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);

    clientSocket->write("{\"type\": \"welcomMessage\", \"message\": \"Welcome my new client! Star systray app is currently running.\"}\r\n");
    clientSocket->flush();

    clientSocket->waitForBytesWritten(3000);

    qInfo() << Q_FUNC_INFO << ": Added a client socket:" << clientSocket->peerPort();
}

void star::server::TcpServer::onClientDisconnected()
{
    auto sender = qobject_cast<QTcpSocket *>(QObject::sender());

    qInfo() << Q_FUNC_INFO << ": Removing a client socket:" << sender->peerPort();

    this->_lstSocketClients.removeAll(sender);
    sender->deleteLater();
}

