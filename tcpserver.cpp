#include "tcpserver.h"
#include "force_interface.h"
//应用层
TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCP Server"));

    ContentListWidget = new QListWidget;

    PortLabel = new QLabel(tr("端口："));
    PortLineEdit = new QLineEdit;

    CreateBtn = new QPushButton(tr("Open Server"));

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);

    port=8010;
    PortLineEdit->setText(QString::number(port));
    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));

    QGridLayout *myLayout = new QGridLayout(this);
// command
    QGridLayout *cmdLayout = new QGridLayout(this);
    QPushButton *cmdWorkingBtn = new QPushButton(tr("CMD_WORKING"));
    QPushButton *cmdIdleBtn = new QPushButton(tr("CMD_IDLE"));
    QPushButton *cmdSetFaultBtn = new QPushButton(tr("CMD_SET_FAULT"));
    QPushButton *cmdResetFaultBtn = new QPushButton(tr("CMD_RESET_FAULT"));
    QPushButton *cmdSwitchModeBtn = new QPushButton(tr("CMD_SWITCH_MODE"));
    //QPushButton *cmdDignoseCfgBtn = new QPushButton(tr("CMD_DIGNOSE_CONFIG"));
    //QPushButton *cmdGetStateBtn = new QPushButton(tr("CMD_GET_STATE"));
    cmdLayout->addWidget(cmdWorkingBtn,1,0);
    cmdLayout->addWidget(cmdIdleBtn,2,0);
    cmdLayout->addWidget(cmdSetFaultBtn,3,0);
    cmdLayout->addWidget(cmdResetFaultBtn,4,0);
    //cmdLayout->addWidget(cmdGetStateBtn,7,0);
    myLayout->addLayout(cmdLayout,0,0,Qt::AlignTop);

    QGridLayout *configLayout = new QGridLayout(this);
    // 创建分组对象
    QGroupBox *modeGroup = new QGroupBox(this);
    QGroupBox *submodeGroup = new QGroupBox(this);
    QGridLayout *modeLayout = new QGridLayout(this);
    QGridLayout *submodeLayout = new QGridLayout(this);

    modeGroup->setTitle("Mode");
    // 创建多选框对象：指定其父对象为分组控件
    QRadioButton *impedBox = new QRadioButton("IMPEDANCE_MODE", modeGroup);
    QRadioButton *admitBox = new QRadioButton("ADMITTANCE_MODE", modeGroup);
    modeLayout->addWidget(impedBox,0,0);
    modeLayout->addWidget(admitBox,0,1);
    modeGroup->setLayout(modeLayout);
    submodeGroup->setTitle("SubMode");
    QRadioButton *teachBox = new QRadioButton("TEACH", submodeGroup);
    QRadioButton *learnBox = new QRadioButton("LEARN", submodeGroup);
    submodeLayout->addWidget(teachBox,1,0);
    submodeLayout->addWidget(learnBox,1,1);
    submodeGroup->setLayout(submodeLayout);

    configLayout->addWidget(modeGroup,0,0);
    configLayout->addWidget(submodeGroup,1,0);
    configLayout->addWidget(cmdSwitchModeBtn,2,0);

    myLayout->addLayout(configLayout,1,0,Qt::AlignTop);

// Set Instruction
    lineSend = new QLineEdit();
    sendBtn = new QPushButton("send");
    myLayout->addWidget(lineSend,2,0,Qt::AlignTop);
    myLayout->addWidget(sendBtn,3,0,Qt::AlignTop);

    connect(cmdWorkingBtn,&QPushButton::clicked,this,&TcpServer::slotCmdWorking);
    connect(cmdIdleBtn,&QPushButton::clicked,this,&TcpServer::slotCmdIdle);
    connect(cmdSetFaultBtn,&QPushButton::clicked,this,&TcpServer::slotCmdSetFault);
    connect(cmdResetFaultBtn,&QPushButton::clicked,this,&TcpServer::slotCmdResetFault);
    connect(sendBtn,&QPushButton::clicked,this,&TcpServer::slotSendMsg);


    mainLayout->addLayout(myLayout,0,3);
}

TcpServer::~TcpServer()
{
    
}

void TcpServer::slotCreateServer()
{
    server = new Server(this,port);
    connect(server,SIGNAL(sigServerRecv(char*,int)),this,SLOT(slotServerRecv(char*,int)));
    connect(this,&TcpServer::signaleSendMsg,server,&Server::slotSendToClients);
    CreateBtn->setEnabled(false);
}

void TcpServer::slotServerRecv(char *msg,int length)
{
    QString msg_qstr = QLatin1String(msg);
    ContentListWidget->addItem(msg_qstr);
}

void TcpServer::slotSendMsg()
{
     QString lineStr = lineSend->text();
     emit signaleSendMsg(lineStr.toLatin1().data(),lineStr.size());
}

void TcpServer::slotCmdWorking()
{
    char buff[1024] = {0};
    ServoCoreProcessCall_t *ptr = (ServoCoreProcessCall_t*)buff;
    ptr->cmd = CMD_WORKING;
    emit signaleSendMsg(buff,1024);
}
void TcpServer::slotCmdIdle()
{
    char buff[1024] = {0};
    ServoCoreProcessCall_t *ptr = (ServoCoreProcessCall_t*)buff;
    ptr->cmd = CMD_IDLE;
    emit signaleSendMsg(buff,1024);
}
void TcpServer::slotCmdSetFault()
{
    char buff[1024] = {0};
    ServoCoreProcessCall_t *ptr = (ServoCoreProcessCall_t*)buff;
    ptr->cmd = CMD_SET_FAULT;
    emit signaleSendMsg(buff,1024);
}
void TcpServer::slotCmdResetFault()
{
    char buff[1024] = {0};
    ServoCoreProcessCall_t *ptr = (ServoCoreProcessCall_t*)buff;
    ptr->cmd = CMD_RESET_FAULT;
    emit signaleSendMsg(buff,1024);
}
