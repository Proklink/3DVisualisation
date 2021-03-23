#ifndef BILLET_H
#define BILLET_H

#include <Qt3DCore>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

using namespace Qt3DCore;
using namespace Qt3DExtras;

class Billet
{
public:
    QCuboidMesh *cub;
    QPhongMaterial *cubMaterial;
    Qt3DCore::QTransform *cubTransform;




    Billet();
    Billet(QEntity *resultEntity);
    ~Billet();
};

#endif // BILLET_H
