#include "billet.h"

Billet::Billet()
{

}


Billet::Billet(QEntity *resultEntity)
{
    xSize = 25;
    ySize = 5;
    zSize = 15;

    //создаем мелкие кубики
    for (int z = 0; z < zSize; z++) {
        QVector<QVector<QEntity *>> yxvector;

        for (int y = 0; y < ySize; y++) {
            QVector<QEntity *> xvector;

            for (int x = 0; x < xSize; x++) {
                //сущность кубика
                QEntity *vexelEntity = new QEntity(resultEntity);

                //фигура куба в QT
                QCuboidMesh *vexel = new QCuboidMesh;
                //размеры куба
                vexel->setXExtent(2);
                vexel->setYExtent(2);
                vexel->setZExtent(2);

                //объект характеристик фигуры
                Qt3DCore::QTransform *vexelTransform = new Qt3DCore::QTransform();
                //смещаем так, чтобы кубики плотно прижимались друг к другу и образовывали большой параллелепипед
                vexelTransform->setTranslation(QVector3D(-xSize + x * 2, -ySize + y * 2, -zSize + z * 2));

                //материал для фигуры, без этого объекта фигуру не будет видно.
                //Это самый простой и маловесящий материал из всех, за исключением, может, кастомной текстуры,
                //я не смог понять как её прикрутить
                QPhongMaterial *vexelMaterial = new QPhongMaterial(resultEntity);
                //устанавливаем цвет
                vexelMaterial->setDiffuse(QColor(QRgb(0x35682d)));

                //добавляем к сущности кубика его составляющие
                vexelEntity->addComponent(vexelMaterial);
                vexelEntity->addComponent(vexel);
                vexelEntity->addComponent(vexelTransform);

                xvector.push_back(vexelEntity);
            }
            yxvector.push_back(xvector);
        }
        billet.push_back(yxvector);
    }


}

Billet::~Billet() {
    for (int i = 0; i < billet.size(); i++) {
        for (int j = 0; j < billet[i].size(); j++)
            for (int k = 0; k < billet[i][j].size(); k++)
                delete billet[i][j][k];
    }
}
