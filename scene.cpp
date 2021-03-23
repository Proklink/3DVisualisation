#include "scene.h"

Scene::Scene()
{
    rootEntity = createScene();

    camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1, 1000);
    camera->setPosition(QVector3D(0.0f, 40.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    cameraController = new QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0f);
    cameraController->setLinearSpeed(50.0f);

    view.setRootEntity(rootEntity);
}

Scene::~Scene() {
    if (camera)
        delete camera;
    if (cameraController)
        delete cameraController;
    if (rootEntity)
        delete rootEntity;

}

QEntity *Scene::createScene() {

    QEntity *resultEntity = new QEntity;

    Billet *billet = new Billet(resultEntity);


    cubTransformAnimation = new QPropertyAnimation();
    cubTransformAnimation->setTargetObject(billet->cub);
    cubTransformAnimation->setStartValue(QVector3D(0.0f, 0.0f, 0.0f));
    cubTransformAnimation->setEndValue(QVector3D(0.0f, 0.0f, -100.0f));
    cubTransformAnimation->setDuration(10000);
    cubTransformAnimation->start();


    resultEntity->addComponent(billet->cub);
    resultEntity->addComponent(billet->cubMaterial);
    resultEntity->addComponent(billet->cubTransform);


    QEntity *lightEntity = new QEntity(resultEntity);
    Qt3DRender::QPointLight *pointLight = new Qt3DRender::QPointLight(resultEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(resultEntity);
    lightTransform->setTranslation(QVector3D(-40.0f, 40.0f, 30.0f));

    lightEntity->addComponent(pointLight);
    lightEntity->addComponent(lightTransform);

    return resultEntity;
}
