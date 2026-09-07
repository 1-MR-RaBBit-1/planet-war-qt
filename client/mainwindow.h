#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QInputDialog>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <QColor>
#include <QTimer>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTexture>
#include <Qt3DExtras/QTextureMaterial>
#include <QFile>

struct MeteoriteData
{
    int id;
    QVector3D position;
    bool direction;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpSocket *socket;
    QVector<Qt3DCore::QTransform*> meteoriteTransforms;
    QVector<Qt3DCore::QEntity*> meteoriteEntities;
    QVector<bool> Ripened;
    QVector<bool> meteoriteFired;
    // QList<bool> meteoriteCreated;
    QVector<bool> meteoriteActive;
    
};

#endif // MAINWINDOW_H