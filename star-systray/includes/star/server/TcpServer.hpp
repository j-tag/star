#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QObject>
#include <QPointer>
#include <QTcpServer>

namespace star {

namespace server {

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer();
    virtual ~TcpServer();

    void initServer();

public slots:
    void onNewConnection();
    void onClientDisconnected();

private:
    QPointer<QTcpServer> _pServer;
    QList<QTcpSocket*> _lstSocketClients;
};

}

}

#endif // TCPSERVER_HPP
