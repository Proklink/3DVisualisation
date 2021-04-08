#include "scene.h"

Scene::Scene() : QObject()
{
    rootEntity = createScene();

    //Создаем и направляем камеру
    camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1, 1000);
    camera->setPosition(QVector3D(0.0f, 40.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    //создаем возможность крутить камерой (здесь надо что то поменять, чтобы передвигать камерой можно было интуитивно)
    cameraController = new QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0f);
    cameraController->setLinearSpeed(50.0f);

    view.setRootEntity(rootEntity);
    //таймер, нужный для анимации
    tmr = new QTimer();

    QObject::connect(tmr, SIGNAL(timeout()), this, SLOT(runMover()));
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
}

QEntity *Scene::createScene() {
    //сущность всей сцены
    QEntity *resultEntity = new QEntity;

    //сущности заготовки и ножа
    billet = new Billet(resultEntity);
    knife = new Knife(resultEntity);

    //свет на сцене
    QEntity *lightEntity = new QEntity(resultEntity);
    Qt3DRender::QPointLight *pointLight = new Qt3DRender::QPointLight(resultEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(resultEntity);
    lightTransform->setTranslation(QVector3D(-40.0f, 40.0f, 30.0f));

    lightEntity->addComponent(pointLight);
    lightEntity->addComponent(lightTransform);

    return resultEntity;
}

//метод для плавного движения объекта
//каждые 10 милисекунд он запускается снова и не закончится пока не выполнится 1000 раз
void Scene::runMover() {
    if ( elapsedSteps < 1000 )
        {
            QVector3D delta = QVector3D(0.1f, 0.0f, 0.0f);
            moveKnife( &delta );
            QTimer::singleShot( 10, this, &Scene::runMover );
            elapsedSteps++;
        }
}

//метод для перемещения объекта
void Scene::moveKnife(QVector3D *delta) {
    QVector3D trans = knife->knifeTransform->translation();
    trans = trans + *delta;
    knife->knifeTransform->setTranslation(trans);
}

void Scene::startTestAnimation() {
    runMover();
}
