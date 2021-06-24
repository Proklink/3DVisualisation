#ifndef SCENE_H
#define SCENE_H

#include "billet.h"
#include "knife.h"
#include "animationpart.h"

#include <QtMath>
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

    //////////////////////////////////////
    //// knife animation data
    int elapsedSteps = 0;
    QVector<AnimationPart *> animationParts;
    int currentPart = 0;

    float discretShift = 0.1f;

    int xStart, xEnd, yStart, yEnd, zStart, zEnd;
    //////////////////////////////////////

    Scene();
    virtual ~Scene();

    QEntity *createScene();
    void setAnimationBounds(int xStart, int xEnd, int yStart, int yEnd, int zStart, int zEnd);
    void createAnimationParts();
    void prepareIntro();
    void backToStart(int xStart, int xEnd, int zStart, int zEnd);

    void checkIntersects();

    void startAutoAnimation();
    void startStepAnimation();
    void runStepMover();
    void moveKnife(QVector3D *delta);


    bool isStepAnimationNow = false;
    bool isAutoAnimationNow = false;


private slots:
    void runMover();



signals:
    void stopTmr();


};

#endif // SCENE_H
