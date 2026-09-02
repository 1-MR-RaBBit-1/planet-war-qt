#include "mainwindow.h"
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralW = new QWidget(this);
    setCentralWidget(centralW);
    QHBoxLayout *HB1 = new QHBoxLayout(centralW);
    QLineEdit *message = new QLineEdit(centralW);
    message->setPlaceholderText("pls enter somthing");
    QPushButton *send = new QPushButton("send",centralW);
    HB1->addWidget(message);
    HB1->addWidget(send);

    socket = new QTcpSocket(this);

    socket->connectToHost(QHostAddress::LocalHost, 5000);

    connect(socket, &QTcpSocket::connected, this, [=]() {
        qDebug() << "Connected to server!";
        // QString text = QInputDialog::getText(this,"Send Data","Enter something:");
        connect(send,&QPushButton::clicked,this,[=](){
            QDataStream stream(socket);
            QString text = message->text();
            stream << text;
            message->clear();
        });
    });
}

MainWindow::~MainWindow() = default;