#include "server.h"
//逻辑层
Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}
/*虚函数实现：客户端有数据过来怎么处理？客户端失去连接怎么处理？*/
void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(sigRecvFromClients(char*,int)),this,SLOT(slotRecvFromClients(char*,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));

    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocketList.append(tcpClientSocket);
}

/*收到了一条客户端消息*/
void Server::slotRecvFromClients(char *msg,int length)
{
    emit sigServerRecv(msg,length);
}
void Server::slotSendToClients(char *msg,int length)
{
    //emit sigServerRecv(msg,length);
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg,length)!=length)
        {
            continue;
        }
    }
}
/*某客户端断开连接，关闭该socket*/
void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
