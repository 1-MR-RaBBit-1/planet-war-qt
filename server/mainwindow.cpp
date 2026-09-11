#include "mainwindow.h"
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    clientSocket = nullptr;
    meteoriteActive.resize(5);
    meteoriteFired.resize(5);
    meteoriteEntities.resize(5);
    meteoriteTransforms.resize(5);
    meteoriteNames.resize(5);
    Ripened.resize(5);
    RipenedME.resize(5);
    RipenedMT.resize(5);
    RipenedNames.resize(5);

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

    QHBoxLayout *HB1 = new QHBoxLayout();

    QLineEdit *sendmessage = new QLineEdit(centralW);
    sendmessage->setPlaceholderText("pls enter somthing");
    QPushButton *send = new QPushButton("send", centralW);
    HB1->addWidget(sendmessage);
    HB1->addWidget(send);

    QGridLayout *control = new QGridLayout();
    
    QLabel *label1 = new QLabel("ip address:");
    control->addWidget(label1, 0, 0);
    QLineEdit *IpC = new QLineEdit();
    control->addWidget(IpC, 0, 1);
    QPushButton *Connect = new QPushButton();
    Connect->setText("Connect");
    control->addWidget(Connect, 0, 2);
    QPushButton *addM = new QPushButton();
    addM->setText("add Metorate");
    control->addWidget(addM, 1, 0);
    QLabel *label2 = new QLabel("metorate Name:");
    control->addWidget(label2, 1, 1);
    QLineEdit *metorateName = new QLineEdit();
    control->addWidget(metorateName, 1, 2);
    QPushButton *Fire = new QPushButton();
    Fire->setText("Fire");
    control->addWidget(Fire, 1, 3);

    VB1->addWidget(Container);
    VB1->addWidget(message);
    VB1->addLayout(HB1);
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
    //مختصات اولیه 
    ETransform->setTranslation(QVector3D(0, 0, 0));

    Qt3DRender::QTexture2D *ETexture = new Qt3DRender::QTexture2D();
    Qt3DRender::QTextureImage *ETextureImage = new Qt3DRender::QTextureImage();
    ETextureImage->setSource(QUrl("qrc:/models/earth.png"));
    ETexture->addTextureImage(ETextureImage);
    Qt3DExtras::QTextureMaterial *EMaterial = new Qt3DExtras::QTextureMaterial();
    EMaterial->setTexture(ETexture);

    earthE->addComponent(earthM);
    earthE->addComponent(ETransform);
    earthE->addComponent(EMaterial);

    //send
    for (int i = 0; i < 5; i++) {

        auto *meteoriteM = new Qt3DRender::QMesh();
        meteoriteM->setSource(
            QUrl("qrc:/models/metorate.obj")
        );

        auto *meteoriteE =
            new Qt3DCore::QEntity(rootEntity);

        auto *transform =
            new Qt3DCore::QTransform();

        auto *texture =
            new Qt3DRender::QTexture2D();

        auto *textureImage =
            new Qt3DRender::QTextureImage();

        textureImage->setSource(
            QUrl("qrc:/models/meteor_texture.png")
        );

        texture->addTextureImage(textureImage);

        auto *material =
            new Qt3DExtras::QTextureMaterial();

        material->setTexture(texture);

        transform->setScale(0.9f);
        transform->setTranslation(
            QVector3D(-1.7f, 0, 0)
        );

        meteoriteE->addComponent(meteoriteM);
        meteoriteE->addComponent(transform);
        meteoriteE->addComponent(material);

        meteoriteEntities[i] = meteoriteE;
        meteoriteTransforms[i] = transform;

        meteoriteActive[i] = false;
        meteoriteFired[i] = false;

        meteoriteE->setEnabled(false);
    }


    //ripend
    for (int i = 0; i < 5; i++) {

        auto *meteoriteM = new Qt3DRender::QMesh();
        meteoriteM->setSource(
            QUrl("qrc:/models/metorate.obj")
        );

        auto *meteoriteE =
            new Qt3DCore::QEntity(rootEntity);

        auto *transform =
            new Qt3DCore::QTransform();

        auto *texture =
            new Qt3DRender::QTexture2D();

        auto *textureImage =
            new Qt3DRender::QTextureImage();

        textureImage->setSource(
            QUrl("qrc:/models/meteor_texture.png")
        );

        texture->addTextureImage(textureImage);

        auto *material =
            new Qt3DExtras::QTextureMaterial();

        material->setTexture(texture);

        transform->setScale(0.9f);
        transform->setTranslation(
            QVector3D(15.0f, 0, 0)
        );

        meteoriteE->addComponent(meteoriteM);
        meteoriteE->addComponent(transform);
        meteoriteE->addComponent(material);

        RipenedME[i] = meteoriteE;
        RipenedMT[i] = transform;

        meteoriteE->setEnabled(false);
    }


    connect(addM, &QPushButton::clicked, this, [=](){
        // for (int i = 0; i < 5; i++){
        //     if (!meteoriteCreated[i]){
        //         meteoriteCreated[i] = true;
        //         Qt3DRender::QMesh *metoriteM = new Qt3DRender::QMesh();
        //         metoriteM->setSource(QUrl("qrc:/models/metorate.obj"));
        //         auto metoriteE = new Qt3DCore::QEntity(rootEntity);
        //         // metoriteM->setRadius(0.5f);
        //         auto transform = new Qt3DCore::QTransform();
        
        //         Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();

        //         Qt3DRender::QTextureImage *textureImage =
        //             new Qt3DRender::QTextureImage();

        //         textureImage->setSource(
        //             QUrl("qrc:/models/meteor_texture.png")
        //         );

        //         transform->setScale(0.9f);
        //         transform->setTranslation(QVector3D(-1.7,0,0));
        

        //         texture->addTextureImage(textureImage);

        //         Qt3DExtras::QTextureMaterial *material =
        //             new Qt3DExtras::QTextureMaterial();

        //         material->setTexture(texture);
        //         // material1->setDiffuse(QColor(255,0,0));

        //         metorateE->addComponent(metoriteM);
        //         metorateE->addComponent(transform);
        //         metorateE->addComponent(material);

        //         // meteoriteEntities.append(metoriteE);
        //         // meteoriteTransforms.append(transform);
        //         // meteoriteFired.append(false);
        //         meteoriteEntities[i] = metoriteE;
        //         meteoriteTransforms[i] = transform;
        //         meteoriteFired[i] = false;
        //         meteoriteCreated[i] = true;
        //     break;
        //     }
        // }

        QString name = metorateName->text().trimmed();

        if (name.isEmpty()) {
            qDebug() << "Meteorite must have a name!";
            return;
        }

        for (int i = 0; i < 5; i++) {

            if (!meteoriteActive[i]) {

                meteoriteNames[i] = name;
                meteoriteActive[i] = true;
                meteoriteFired[i] = false;

                meteoriteTransforms[i]->setTranslation(QVector3D(-1.7f, 0, 0));

                meteoriteEntities[i]->setEnabled(true);

                break;
            }
        }
        metorateName->clear();

    });


    setWindowTitle("planet War");
    resize(500, 500);

    //دکمه send (ارسال پیام) 
    // اینجا یک بار برای همیشه connect می‌شود
    connect(send, &QPushButton::clicked, this, [=](){
        if (!clientSocket || clientSocket->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "Not connected!";
            return;
        }

        QString text = sendmessage->text().trimmed();
        if (text.isEmpty()) {
            return;
        }

        //  فقط شهاب‌سنگ دریافتی خودم را نابود کن 
        // به meteoriteEntities (شهاب‌سنگ خودی) کاری نداشته باش
        for (int i = 0; i < RipenedNames.size(); i++) {

            if (RipenedNames[i] == text) {

                qDebug() << "Destroying my incoming meteorite:" << text;
                qDebug() << "ID:" << i;

                if (RipenedME[i]) {
                    RipenedME[i]->setEnabled(false);
                }

                RipenedNames[i].clear();
                Ripened[i] = false;

                qDebug() << "Incoming meteorite destroyed!";

                break;
            }
        }

        //  پیام را به طرف مقابل بفرست 
        QDataStream stream(clientSocket);
        stream << 1;  // نوع پیام: متن
        stream << text;

        sendmessage->clear();
        qDebug() << "Text sent:" << text;
    });

    //  سرور 
    server = new QTcpServer(this);

    // برای برنامه اول: 127.0.0.1
    // برای برنامه دوم: 127.0.0.2
    server->listen(QHostAddress("127.0.0.1"), 5000);

    qDebug() << "Server is listening...";

    connect(server, &QTcpServer::newConnection, this, [=]() {

        clientSocket = server->nextPendingConnection();

        ETransform->setTranslation(QVector3D(-4, 0, 0));

        connect(clientSocket, &QTcpSocket::readyRead, this, [=](){
            QDataStream stream(clientSocket);
            
            int msgType;
            stream >> msgType;
            
            if (msgType == 1) {

                QString text;
                stream >> text;

                message->setText(text);

                qDebug() << "Text received:" << text;

                //  فقط شهاب‌سنگ دریافتی نابود می‌شود 
                // شهاب‌سنگ خودی (meteoriteEntities) اصلاً دست نمی‌خورد
                for (int i = 0; i < RipenedNames.size(); i++) {

                    if (RipenedNames[i] == text) {

                        qDebug() << "Received meteorite found!";
                        qDebug() << "ID:" << i;
                        qDebug() << "Name:" << RipenedNames[i];

                        if (RipenedME[i]) {
                            RipenedME[i]->setEnabled(false);
                        }

                        RipenedNames[i].clear();
                        Ripened[i] = false;

                        qDebug() << "Remote meteorite destroyed!";

                        break;
                    }
                }
            }
            else if (msgType == 2) {
                stream.startTransaction();

                // int id;
                // QVector3D position;
                // bool direction;
                MeteoriteData data;
                stream >> data.id;
                stream >> data.name;
                stream >> data.position;
                stream >> data.direction;

                if (!stream.commitTransaction()) {
                    return;
                }

                qDebug() << "meteorite received!";
                qDebug() << "ID:" << data.id;
                qDebug() << "NAME:" << data.name;
                qDebug() << "POSITION:" << data.position;
                qDebug() << "DIRECTION:" << data.direction;

                if (data.id < 0 || data.id >= RipenedME.size()) {
                    qDebug() << "Invalid meteorite ID!";
                    return;
                }

                if (!RipenedME[data.id] || !RipenedMT[data.id]) {
                    qDebug() << "Meteorite pointers are invalid!";
                    return;
                }

                // اسم شهاب‌سنگ دریافتی را ذخیره می‌کنیم
                RipenedNames[data.id] = data.name;
                Ripened[data.id] = true;

                auto *transform = RipenedMT[data.id];
                auto *meteoriteE = RipenedME[data.id];

                transform->setTranslation(
                    QVector3D(15.0f, 0, 0)
                );

                meteoriteE->setEnabled(true);

                auto *timer = new QTimer(this);

                connect(timer, &QTimer::timeout, this, [=]() {

                    QVector3D pos = transform->translation();

                    pos.setX(pos.x() - 0.05f);

                    transform->setTranslation(pos);

                    qDebug() << "Remote meteorite X =" << pos.x();

                    if (pos.x() <= data.position.x()) {

                        timer->stop();
                        timer->deleteLater();

                        qDebug() << "Remote meteorite reached target!";
                    }
                });

                timer->start(16);
            }
        });

        connect(clientSocket, &QTcpSocket::connected, this, [=]() {
            ETransform->setTranslation(QVector3D(-4, 0, 0));
            qDebug() << "Connected to server!";
        });

        qDebug() << "Client connected!";
    });

    //  دکمه Connect (اتصال به عنوان کلاینت) 
    connect(Connect, &QPushButton::clicked, this, [=](){
        QString ip = IpC->text().trimmed();
        if(ip.isEmpty()){
            qDebug() << "Please enter server IP!";
            return;
        }
        
        if (!clientSocket) {
            clientSocket = new QTcpSocket(this);
            
            connect(clientSocket, &QTcpSocket::readyRead, this, [=](){
            QDataStream stream(clientSocket);
            
            int msgType;
            stream >> msgType;
            
            if (msgType == 1) {

                QString text;
                stream >> text;
            
                message->setText(text);

                qDebug() << "Text received:" << text;

                //  فقط شهاب‌سنگ دریافتی نابود می‌شود 
                for (int i = 0; i < RipenedNames.size(); i++) {

                    if (RipenedNames[i] == text) {

                        qDebug() << "Received meteorite found!";
                        qDebug() << "ID:" << i;
                        qDebug() << "Name:" << RipenedNames[i];

                        if (RipenedME[i]) {
                            RipenedME[i]->setEnabled(false);
                        }

                        RipenedNames[i].clear();
                        Ripened[i] = false;

                        qDebug() << "Remote meteorite destroyed!";

                        break;
                    }
                }
            }
                else if (msgType == 2) {
                    // int id;
                    // QVector3D position;
                    // bool direction;
                    stream.startTransaction();
                    MeteoriteData data;
                    stream >> data.id;
                    stream >> data.name;
                    stream >> data.position;
                    stream >> data.direction;

                    if (!stream.commitTransaction()) {
                    return;
                    }
                    
                    qDebug() << "Meteorite received!";
                    qDebug() << "ID:" << data.id;
                    qDebug() << "NAME:" << data.name;
                    qDebug() << "POSITION:" << data.position;
                    qDebug() << "DIRECTION:" << data.direction;
                    
                    if (data.id >= 0 && data.id < RipenedME.size() && RipenedME[data.id] && RipenedMT[data.id]) {

                        RipenedNames[data.id] = data.name;
                        Ripened[data.id] = true;

                        auto *transform = RipenedMT[data.id];
                        auto *meteoriteE = RipenedME[data.id];

                        transform->setTranslation(QVector3D(15.0f, 0, 0));
                        meteoriteE->setEnabled(true);
                        
                        auto *timer = new QTimer(this);

                        connect(timer, &QTimer::timeout, this, [=]() {
                            QVector3D pos = transform->translation();
                            pos.setX(pos.x() - 0.05f);
                            transform->setTranslation(pos);

                            if (pos.x() <= data.position.x()) {
                                timer->stop();
                                timer->deleteLater();
                            }
                        });

                        timer->start(16);
                    }
                }
            });
            
            connect(clientSocket, &QTcpSocket::connected, this, [=]() {
                ETransform->setTranslation(QVector3D(-4, 0, 0));
                qDebug() << "Connected to server!";
            });
        }
        
        qDebug() << "Connecting to:" << ip;
        clientSocket->connectToHost(ip, 5000);
    });

    //  دکمه Fire (پرتاب شهاب‌سنگ) 
    connect(Fire, &QPushButton::clicked, this, [=]() {

        if (!clientSocket || clientSocket->state() != QAbstractSocket::ConnectedState) {
            qDebug() << "Client is not connected!";
            return;
        }
        for (int i = 0; i < meteoriteFired.size(); i++) {

            if (meteoriteActive[i] && !meteoriteFired[i]) {
                MeteoriteData meteoriteData;

                meteoriteData.id = i;
                meteoriteData.name = meteoriteNames[i];
                meteoriteData.position = meteoriteTransforms[i]->translation();
                meteoriteData.direction = true;

                if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState){
                    QDataStream stream(clientSocket);
                    stream << 2;  // نوع پیام: شهاب‌سنگ
                    stream << meteoriteData.id;
                    stream << meteoriteData.name;
                    stream << meteoriteData.position;
                    stream << meteoriteData.direction;
                    meteoriteFired[i] = true;
                    qDebug() << "Meteorite sent! ID:" << i;
                }

                auto *transform = meteoriteTransforms[i];
                auto *meteoriteE = meteoriteEntities[i];

                auto *timer = new QTimer(this);

                connect(timer, &QTimer::timeout, this, [=]() {

                    QVector3D pos = transform->translation();

                    qDebug() << "Meteorite" << i << "X =" << pos.x();

                    pos.setX(pos.x() + 0.05f);

                    transform->setTranslation(pos);

                    if (pos.x() >= 12.0f) {

                        timer->stop();
                        timer->deleteLater();

                        // meteoriteE->deleteLater();
                        meteoriteE->setEnabled(false);

                        meteoriteActive[i] = false;
                        meteoriteFired[i] = false; 
                        // meteoriteEntities[i] = nullptr;
                        // meteoriteTransforms[i] = nullptr;
                    }
                });

                timer->start(16);

                break;
            }
        }
    });
}

MainWindow::~MainWindow() = default;