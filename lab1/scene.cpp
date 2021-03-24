#include "scene.h"

Scene::Scene() : QObject()
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

}

QEntity *Scene::createScene() {

    QEntity *resultEntity = new QEntity;

    billet = new Billet(resultEntity);

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

void Scene::runMover() {
    if ( elapsedSteps < 1000 )
        {
            QVector3D delta = QVector3D(0.0f, 0.0f, -0.1f);
            moveCube( &delta );
            //QTimer::singleShot( 10, this, &Scene::runMover );
            elapsedSteps++;
        }
}

void Scene::moveCube(QVector3D *delta) {
    QVector3D trans = billet->cubTransform->translation();
    trans = trans + *delta;
    billet->cubTransform->setTranslation(trans);
}

void Scene::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == 1055)
    {
        std::cout << "Animation has started" << std::endl;
        runMover();
    }

}
