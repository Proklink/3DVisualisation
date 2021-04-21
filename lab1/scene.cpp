#include "scene.h"

Scene::Scene() : QObject()
{
    rootEntity = createScene();

    //Создаем и направляем камеру
    camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1, 1000);
    camera->setPosition(QVector3D(12.5f, 20.0f, 40.0f));
    camera->setViewCenter(QVector3D(12.5f, 0.0f, 7.5f));


    //создаем возможность крутить камерой (здесь надо что то поменять, чтобы передвигать камерой можно было интуитивно)
    cameraController = new QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0f);
    cameraController->setLinearSpeed(50.0f);

    view.setRootEntity(rootEntity);
    //таймер, нужный для анимации
    tmr = new QTimer();

    QObject::connect(tmr, SIGNAL(timeout()), this, SLOT(runMover()));
    QObject::connect(this, SIGNAL(stopTmr()), tmr, SLOT(stop()));
}



Scene::~Scene() {
    if (camera)
        delete camera;
    if (cameraController)
        delete cameraController;
    if (rootEntity)
        delete rootEntity;
    if (billet)
        delete billet;
    if (knife)
        delete knife;
    if (tmr)
        delete tmr;

    for (int i = 0; i < animationParts.size(); i++)
        delete animationParts[i];
}

QEntity *Scene::createScene() {
    //сущность всей сцены
    QEntity *resultEntity = new QEntity;

    //сущности заготовки и ножа
    billet = new Billet(resultEntity);
    knife = new Knife(resultEntity);

    //свет на сцене
    QEntity *lightEntity2 = new QEntity(resultEntity);
    Qt3DRender::QPointLight *pointLight2 = new Qt3DRender::QPointLight(resultEntity);
    Qt3DCore::QTransform *lightTransform2 = new Qt3DCore::QTransform(resultEntity);
    lightTransform2->setTranslation(QVector3D(-20.0f, 40.0f, 30.0f));

    lightEntity2->addComponent(pointLight2);
    lightEntity2->addComponent(lightTransform2);

    //свет на сцене
    QEntity *lightEntity3 = new QEntity(resultEntity);
    Qt3DRender::QPointLight *pointLight3 = new Qt3DRender::QPointLight(resultEntity);
    Qt3DCore::QTransform *lightTransform3 = new Qt3DCore::QTransform(resultEntity);
    lightTransform3->setTranslation(QVector3D(60.0f, -40.0f, -30.0f));

    lightEntity3->addComponent(pointLight3);
    lightEntity3->addComponent(lightTransform3);

    return resultEntity;
}

void Scene::setAnimationBounds(int xStart, int xEnd, int yStart, int yEnd, int zStart, int zEnd) {
    if (xStart > xEnd) {
        int temp = xEnd;
        xEnd = xStart;
        xStart = temp;
    }
    if (zStart > zEnd) {
        int temp = zEnd;
        zEnd = zStart;
        zStart = temp;
    }
    if (yStart < yEnd) {
        int temp = yEnd;
        yEnd = yStart;
        yStart = temp;
    }

    this->xStart = xStart;
    this->xEnd = xEnd;
    this->yStart = yStart;
    this->yEnd = yEnd;
    this->zStart = zStart;
    this->zEnd = zEnd;
}

//перемещаем нож из начального положение в точку, от которой начнется выпиливание
void Scene::prepareIntro() {
    AnimationPart *animPart = new AnimationPart(
                                                QVector3D(discretShift, 0.0f, 0.0f),
                                                knife->knifeTransform->translation().x() + knife->knifeFigure->xExtent() / 2,
                                                xStart );
    animationParts.push_back(animPart);

    animPart = new AnimationPart(
                                 QVector3D(0.0f, 0.0f, discretShift),
                                 knife->knifeTransform->translation().z(),
                                 zStart - 1);
    animationParts.push_back(animPart);

    animPart = new AnimationPart(
                                 QVector3D(0.0f, -discretShift, 0.0f),
                                 knife->knifeTransform->translation().y(),
                                 knife->knifeTransform->translation().y() - 1);
    animationParts.push_back(animPart);
}

void Scene::backToStart(int xStart, int xEnd, int zStart, int zEnd) {
    AnimationPart *animPart = new AnimationPart(
                                                QVector3D(-discretShift, 0.0f, 0.0f),
                                                xStart,
                                                xEnd );
    animationParts.push_back(animPart);

    animPart = new AnimationPart(
                                 QVector3D(0.0f, 0.0f, -discretShift),
                                 zStart,
                                 zEnd );
    animationParts.push_back(animPart);

}

void Scene::createAnimationParts() {
    //knife->knifeTransform->setTranslation(QVector3D(0.0f - 0.5f - knife->knifeFigure->xExtent() / 2, 0.0f + 10, 0.0f));
    prepareIntro();

    AnimationPart *animPart;

    for (int y = yStart; y > yEnd - 1; y--) {

        animPart = new AnimationPart(
                                     QVector3D(0.0f, -discretShift, 0.0f),
                                     0,
                                     1);
        animationParts.push_back(animPart);

        for (int z = 0; z < abs(zEnd - zStart) + 1; z++) {
            float xDiscretShift;

            //сначала идем в одну сторону, затем в другую
            if ((z % 2) == 0)
                xDiscretShift = discretShift;
            else
                xDiscretShift = -discretShift;

            //проходимся ножом по линии x
            animPart = new AnimationPart(
                                         QVector3D(xDiscretShift, 0.0f, 0.0f),
                                         xStart,
                                         xEnd);
            animationParts.push_back(animPart);

            if (z != abs(zEnd - zStart)) {

                //поднимаем нож
                animPart = new AnimationPart(
                                             QVector3D(0.0f, discretShift, 0.0f),
                                             knife->knifeTransform->translation().y(),
                                             knife->knifeTransform->translation().y() + 1);
                animationParts.push_back(animPart);

                //передвигаем  нож
                animPart = new AnimationPart(
                                             QVector3D(0.0f, 0.0f, discretShift),
                                             knife->knifeTransform->translation().z(),
                                             knife->knifeTransform->translation().z() + 1);
                animationParts.push_back(animPart);

                //опускаем нож
                animPart = new AnimationPart(
                                             QVector3D(0.0f, -discretShift, 0.0f),
                                             knife->knifeTransform->translation().y(),
                                             knife->knifeTransform->translation().y() - 1);
                animationParts.push_back(animPart);
            }
            else {
                if (z % 2 == 0)
                    backToStart(xStart, xEnd, zStart, zEnd);
                else
                    backToStart(0, 0, zStart, zEnd);
            }

        }
    }


}


void Scene::checkIntersects() {
    QVector3D trans = knife->knifeTransform->translation();
    float xKnifePos;

    if (animationParts[currentPart]->delta.x() > 0)
        xKnifePos = trans.x() - knife->knifeFigure->xExtent() / 2;
    else
        xKnifePos = trans.x() + knife->knifeFigure->xExtent() / 2 - 0.1f;
    float yKnifePos = trans.y() - knife->knifeFigure->yExtent() / 2 + 0.48;
    float zKnifePos = trans.z();

    if (((xKnifePos >= xStart - 1) && (xKnifePos <= xEnd)) &&
        ((zKnifePos >= zStart - 1) && (zKnifePos <= zEnd)) &&
            ((yKnifePos <= yStart) && (yKnifePos >= yEnd - 1)))
    {
        QEntity *vexelEntity = billet->billet[(int)yKnifePos][(int)zKnifePos][(int)xKnifePos];
        vexelEntity->setEnabled(false);

    }

}


//метод для плавного движения объекта
//каждые 10 милисекунд он запускается снова и не закончится пока не выполнится 1000 раз
void Scene::runMover() {
    AnimationPart *animPart = animationParts[currentPart];
    int reqSteps = abs(animPart->end - animPart->start) / discretShift;

    if ( elapsedSteps < reqSteps )
        {
            moveKnife( &animPart->delta );
            //QTimer::singleShot( 10, this, &Scene::runMover );
            //tmr->singleShot( 10, this, &Scene::runMover );
            tmr->start(1);
            elapsedSteps++;
        }
    else {
        if (currentPart < animationParts.size() - 1) {
            elapsedSteps = 0;
            currentPart++;
            runMover();
        }
    }
}

void Scene::runStepMover() {
    AnimationPart *animPart = animationParts[currentPart];
    int reqSteps = abs(animPart->end - animPart->start) / discretShift;

    if ( elapsedSteps < reqSteps )
        {
            moveKnife( &animPart->delta );
            elapsedSteps++;
        }
    else {
        if (currentPart < animationParts.size() - 1) {
            elapsedSteps = 0;
            currentPart++;
        }
    }
}



//метод для перемещения объекта
void Scene::moveKnife(QVector3D *delta) {
    QVector3D trans = knife->knifeTransform->translation();
    trans = trans + *delta;
    knife->knifeTransform->setTranslation(trans);
    checkIntersects();
}

void Scene::startAutoAnimation() {
    createAnimationParts();
    isAutoAnimationNow = true;
    runMover();
}

void Scene::startStepAnimation() {
    if (!isStepAnimationNow)
        createAnimationParts();
    isStepAnimationNow = true;
    runStepMover();
}
