#include "billet.h"

Billet::Billet()
{

}


Billet::Billet(QEntity *resultEntity)
{
    cub = new QCuboidMesh(resultEntity);
    cub->setXExtent(50);
    cub->setYExtent(10);
    cub->setZExtent(30);


    cubMaterial = new QPhongMaterial(resultEntity);

    cubTransform = new Qt3DCore::QTransform(resultEntity);
    cubTransform->setTranslation(QVector3D(0.0f, 0.0f, -20.0f));
}

Billet::~Billet() {

    if (cub)
        delete cub;
    if (cubMaterial)
        delete cubMaterial;
    if (cubTransform)
        delete cubTransform;

}
