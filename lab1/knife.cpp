#include "knife.h"

Knife::Knife(QEntity *resultEntity)
{
    knifeEntity = new QEntity(resultEntity);

    QCuboidMesh *knife = new QCuboidMesh;
    knife->setXExtent(4);
    knife->setYExtent(10);
    knife->setZExtent(2);

    knifeTransform = new Qt3DCore::QTransform();
    knifeTransform->setTranslation(QVector3D(-26.0f, 9.0f, 0.0f));

    QPhongMaterial *knifeMaterial = new QPhongMaterial();
    knifeMaterial->setDiffuse(QColor(QRgb(0x525252)));

    knifeEntity->addComponent(knifeMaterial);
    knifeEntity->addComponent(knife);
    knifeEntity->addComponent(knifeTransform);

}

Knife::~Knife() {
    if (knifeEntity)
        delete knifeEntity;
}
