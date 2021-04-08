#ifndef KNIFE_H
#define KNIFE_H


#include <Qt3DCore>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

using namespace Qt3DCore;
using namespace Qt3DExtras;

class Knife
{
private:

    QEntity *knifeEntity;

public:
     Qt3DCore::QTransform *knifeTransform;


    Knife(QEntity *resultEntity);
    ~Knife();
};

#endif // KNIFE_H
