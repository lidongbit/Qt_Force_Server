#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include "server.h"

class TcpServer : public QDialog
{
    Q_OBJECT
    
public:
    TcpServer(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~TcpServer();    
private:
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;

    int port;
    Server *server;

    QLineEdit *lineSend;
    QPushButton *sendBtn;
public slots:
    void slotCreateServer();
    void slotServerRecv(char*,int);
    void slotSendMsg();
    void slotCmdWorking();
    void slotCmdIdle();
    void slotCmdSetFault();
    void slotCmdResetFault();
signals:
    void signaleSendMsg(char*,int);
};

#endif // TCPSERVER_H
