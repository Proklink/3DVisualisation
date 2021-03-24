#include "scene.h"
#include "mainwindow.h"

#include <iostream>
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
using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Scene *scene = new Scene();

    scene->view.show();

    return app.exec();
}

