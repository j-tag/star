#include "includes/star/Star.hpp"

star::client::TcpClient::TcpClient() {}

star::client::TcpClient::~TcpClient() {}

void star::client::TcpClient::connectToServer(std::function<void()> functor, std::function<void()> functorFail)
{
    this->_pTcpSocket = new QTcpSocket(this);

    connect(this->_pTcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(this->_pTcpSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(this->_pTcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);

    qInfo() << Q_FUNC_INFO << ": Attempting to connect to local TCP server.";

    // Attempting to connect to local TCP server
    this->_pTcpSocket->connectToHost(QHostAddress::LocalHost, 38585);

    // We need to wait for acception from server...
    if(this->_pTcpSocket->waitForConnected(5000)) {
        qInfo() << Q_FUNC_INFO << ": Connected to local TCP socket successfully.";
        functor();
    } else {
        qInfo() << Q_FUNC_INFO << ": Failed to connect to local TCP socket:" << this->_pTcpSocket->errorString();
        functorFail();
    }
}

void star::client::TcpClient::close()
{
    if(this->_pTcpSocket) {
        this->_pTcpSocket->close();
    }
}

void star::client::TcpClient::onConnected()
{
    qInfo() << Q_FUNC_INFO << ": TCP client connected.";
}

void star::client::TcpClient::onDisconnected()
{
    qInfo() << Q_FUNC_INFO << ": TCP client disconnected.";
}

void star::client::TcpClient::onReadyRead()
{
    qInfo() << Q_FUNC_INFO << ": TCP client ready read.";
}
