#ifndef BILLET_H
#define BILLET_H

#include <Qt3DCore>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DExtras/QMetalRoughMaterial>
#include <Qt3DExtras/QMorphPhongMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>

#include <QVector>

using namespace Qt3DCore;
using namespace Qt3DExtras;

class Billet
{
public:
    //сущности мелких кубиков
    QVector <QVector<QVector<QEntity *>>> billet;

    int xSize, ySize, zSize;


    Billet();
    Billet(QEntity *resultEntity);
    ~Billet();
};

#endif // BILLET_H
