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
        QVector3D(0, 0, 20)
    );

    camera->setViewCenter(
        QVector3D(0, 0, 0)
    );
    

    Qt3DRender::QMesh *earthM = new Qt3DRender::QMesh();
    earthM->setSource(QUrl("qrc:/models/earth.obj"));
    Qt3DCore::QEntity *earthE = new Qt3DCore::QEntity(rootEntity);

    Qt3DCore::QTransform *ETransform = new Qt3DCore::QTransform();
    ETransform->setScale(0.5f);

    //مختصات اولیه ی سیاره 
    ETransform->setTranslation(QVector3D(0, 0, 0));

    Qt3DRender::QTexture2D *ETexture = new Qt3DRender::QTexture2D();
    Qt3DRender::QTextureImage *ETextureImage = new Qt3DRender::QTextureImage();
    ETextureImage->setSource(QUrl("qrc:/models/earth.png"));
    ETexture->addTextureImage(ETextureImage);
    Qt3DExtras::QTextureMaterial *EMaterial= new Qt3DExtras::QTextureMaterial();
    EMaterial->setTexture(ETexture);

    earthE->addComponent(earthM);
    earthE->addComponent(ETransform);
    earthE->addComponent(EMaterial);

    connect(addM,&QPushButton::clicked,this,[=](){
        Qt3DRender::QMesh *metoriteM = new Qt3DRender::QMesh();
        metoriteM->setSource(QUrl("qrc:/models/metorate.obj"));
        
        auto *metoriteE = new Qt3DCore::QEntity(rootEntity);

        auto *transform = new Qt3DCore::QTransform(metoriteE);

        transform->setScale(0.9f);
        transform->setTranslation(QVector3D(-2, 0, 0));

        meteoriteEntities.append(metoriteE);
        meteoriteTransforms.append(transform);
        meteoriteFired.append(false);

        // metoriteM->setRadius(0.5f);
        // Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
        // // transform->setScale(0.9f);
        // transform->setTranslation(QVector3D(-1.7,0,0));
        Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();

        Qt3DRender::QTextureImage *textureImage =
            new Qt3DRender::QTextureImage();

        textureImage->setSource(
            QUrl("qrc:/models/meteor_texture.png")
        );

        texture->addTextureImage(textureImage);

        Qt3DExtras::QTextureMaterial *material =
            new Qt3DExtras::QTextureMaterial();

        material->setTexture(texture);
        // material1->setDiffuse(QColor(255,0,0));

        metoriteE->addComponent(metoriteM);
        // metoriteE->addComponent(transform);
        metoriteE->addComponent(transform);
        metoriteE->addComponent(material);
    });


    setWindowTitle("planet War");
    resize(500,500);



    server = new QTcpServer(this);

    server->listen(QHostAddress::LocalHost, 5000);

    qDebug() << "Server is listening...";
    
    connect(Fire, &QPushButton::clicked, this, [=]() {
        for (int i = 0; i < meteoriteFired.size(); i++) {

        if (!meteoriteFired[i]) {

            meteoriteFired[i] = true;

            auto *transform = meteoriteTransforms[i];
            auto *meteoriteE = meteoriteEntities[i];

            auto *timer = new QTimer(this);

            connect(timer, &QTimer::timeout, this, [=]() {

                QVector3D pos = transform->translation();

                qDebug() << "Meteorite" << i
             << "X =" << pos.x();

                pos.setX(pos.x() + 0.05f);

                transform->setTranslation(pos);

                if (pos.x() >= 12.0f) {

                    timer->stop();
                    timer->deleteLater();

                    meteoriteE->deleteLater();

                }
            });

            timer->start(16);

            break;
        }
    }
    });

    connect(server, &QTcpServer::newConnection, this, [=]() {

        QTcpSocket *clientSocket = server->nextPendingConnection();

        ETransform->setTranslation(QVector3D(-4, 0, 0));

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
