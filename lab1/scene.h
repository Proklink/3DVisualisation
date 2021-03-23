#ifndef SCENE_H
#define SCENE_H

#include "billet.h"

#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <QPushButton>

using namespace Qt3DExtras;
using namespace Qt3DCore;

class Scene
{
public:
    Qt3DWindow view;
    QEntity *rootEntity;
    Qt3DRender::QCamera *camera;
    QOrbitCameraController *cameraController;
    QPropertyAnimation *cubTransformAnimation;

//    QEntity *lightEntity;
//    Qt3DRender::QPointLight *pointLight;
//    Qt3DCore::QTransform *lightTransform;


    Scene();

    ~Scene();
    QEntity *createScene();

private:

};

#endif // SCENE_H
