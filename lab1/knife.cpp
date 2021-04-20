#include "knife.h"

Knife::Knife(QEntity *resultEntity)
{
    knifeEntity = new QEntity(resultEntity);

    knifeFigure = new QCuboidMesh;
    knifeFigure->setXExtent(1);
    knifeFigure->setYExtent(5);
    knifeFigure->setZExtent(0.2);

    basePosition = QVector3D(0.0f - knifeFigure->xExtent() / 2, 0.0f +  knifeFigure->yExtent() / 2 + 6, 0.0f + knifeFigure->zExtent() / 2);

    knifeTransform = new Qt3DCore::QTransform();
    knifeTransform->setTranslation(basePosition);

    QPhongMaterial *knifeMaterial = new QPhongMaterial();
    knifeMaterial->setDiffuse(QColor(QRgb(0x525252)));

    knifeEntity->addComponent(knifeMaterial);
    knifeEntity->addComponent(knifeFigure);
    knifeEntity->addComponent(knifeTransform);

}

Knife::~Knife() {
    if (knifeEntity)
        delete knifeEntity;
}
