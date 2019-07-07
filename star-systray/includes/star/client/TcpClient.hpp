#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QPointer>
#include <QTcpSocket>

namespace star {

namespace client {

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient();
    virtual ~TcpClient();

    void connectToServer(std::function<void()> functor, std::function<void()> functorFail);
    void close();

public slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QPointer<QTcpSocket> _pTcpSocket;
};

}

}
#endif // TCPCLIENT_HPP
