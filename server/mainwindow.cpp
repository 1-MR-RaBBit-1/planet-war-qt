#include "mainwindow.h"
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    
    auto *view = new Qt3DExtras::Qt3DWindow();
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    view->setRootEntity(rootEntity);
    QWidget *Container = QWidget::createWindowContainer(view);
    
    QWidget *centralW = new QWidget(this);
    setCentralWidget(centralW);
    QVBoxLayout *VB1 = new QVBoxLayout(centralW);
    QLineEdit *message = new QLineEdit(this);
    message->setPlaceholderText("no message yet ...");
    message->setReadOnly(true);

    QGridLayout *control = new QGridLayout();
    
    QLabel *label1 = new QLabel("ip address:");
    control->addWidget(label1,0,0);
    QLineEdit *IpC = new QLineEdit();
    control->addWidget(IpC,0,1);
    QPushButton *Connect = new QPushButton();
    Connect->setText("Connect");
    control->addWidget(Connect, 0,2);
    QPushButton *addM = new QPushButton();
    addM->setText("add Metorate");
    control->addWidget(addM, 1,0);
    QLabel *label2 = new QLabel("metorate Name:");
    control->addWidget(label2,1,1);
    QLineEdit *metorateName = new QLineEdit();
    control->addWidget(metorateName, 1,2);
    QPushButton *Fire = new QPushButton();
    Fire->setText("Fire");
    control->addWidget(Fire,1,3);
    

    VB1->addWidget(Container);
    VB1->addWidget(message);
    VB1->addLayout(control);

    // Camera
    auto *camera = view->camera();

    camera->setPosition(
        QVector3D(0, 0, 10)
    );

    camera->setViewCenter(
        QVector3D(0, 0, 0)
    );

    connect(addM,&QPushButton::clicked,this,[=](){
        Qt3DExtras::QSphereMesh *metoriteM = new Qt3DExtras::QSphereMesh();
        Qt3DCore::QEntity *metoriteE = new Qt3DCore::QEntity(rootEntity);
        metoriteM->setRadius(0.5f);
        Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
        Qt3DExtras::QPhongMaterial *material1 = new Qt3DExtras::QPhongMaterial();
        material1->setDiffuse(QColor(255,0,0));

        metoriteE->addComponent(metoriteM);
        metoriteE->addComponent(transform);
        metoriteE->addComponent(material1);
    });


    setWindowTitle("planet War");
    resize(500,500);



    server = new QTcpServer(this);

    server->listen(QHostAddress::LocalHost, 5000);

    qDebug() << "Server is listening...";
    
    connect(server, &QTcpServer::newConnection, this, [=]() {

        QTcpSocket *clientSocket = server->nextPendingConnection();

        connect(clientSocket, &QTcpSocket::readyRead, this, [=](){
            QDataStream stream(clientSocket);
            QString text;
            stream >> text;
            message->setText(text);
            // QMessageBox::information(this,"Received Data",text);
            // qDebug() << text;
        });

        qDebug() << "Client connected!";

    });
}

MainWindow::~MainWindow() = default;