#ifndef SCENE_H
#define SCENE_H

#include "billet.h"
#include "knife.h"

#include <QObject>
#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <QPushButton>
#include <QTimer>

#include <iostream>


using namespace Qt3DExtras;
using namespace Qt3DCore;


class Scene : public QObject
{
    Q_OBJECT

public:
    QEntity *rootEntity;

    Qt3DWindow view;
    Qt3DRender::QCamera *camera;
    QOrbitCameraController *cameraController;

    Billet *billet;
    Knife *knife;

    QTimer *tmr;
    int elapsedSteps = 0;

    Scene();
    virtual ~Scene();

    QEntity *createScene();
    void moveKnife(QVector3D *delta);
    void startTestAnimation();

private slots:
    void runMover();



};

#endif // SCENE_H
