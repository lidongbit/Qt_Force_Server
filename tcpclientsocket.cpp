#include "tcpclientsocket.h"
//通信层

/*客户端收到数据怎么处理? 客户端断开连接怎么处理？*/
TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
/*socket 有数据过来就读，读好发出client数据到来信号*/
void TcpClientSocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024] = {0};
        read(buf,length);
        emit sigRecvFromClients(buf,length);
    }
}
/*socket 断开，发出客户端断开信号*/
void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
