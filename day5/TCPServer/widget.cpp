#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = new QTcpServer;
    server->listen(QHostAddress::AnyIPv4, PORT);

    //客户端发起连接, server发出信号
    connect(server, &QTcpServer::newConnection, this, &Widget::newClientHandler);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::newClientHandler()
{
    //建立TCP连接
    QTcpSocket *socket = server->nextPendingConnection();
    // socket->peerAddress(); // 获取客户端地址 QHostAddress
    // socket->peerPort(); // 获取客户端端口号 Quint16

    ui->ipLineEdit->setText(socket->peerAddress().toString());
    ui->portLineEdit->setText(QString::number(socket->peerPort()));

    // 服务器收到客户端发出的信息, socket发出readyread信号
    connect(socket, &QTcpSocket::readyRead, this, &Widget::clientInfoSlot);
}

void Widget::clientInfoSlot()
{
    // 获取newClientHandler的局部变量,获取信号发出者
    QTcpSocket *s = (QTcpSocket *)sender();
    ui->mainLineEdit->setText(QString(s->readAll()));
}
