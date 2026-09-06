#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>

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
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpServer *server;
    QVector<Qt3DCore::QTransform*> meteoriteTransforms;
    QVector<Qt3DCore::QEntity*> meteoriteEntities;
    QVector<bool> meteoriteFired;
};

#endif // MAINWINDOW_H
