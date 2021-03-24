#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QSlider>
#include <QRadioButton>
#include <Qt3DExtras>
#include <QLabel>
#include <QIntValidator>
#include "scene.h"
#include <QKeyEvent>

using namespace Qt3DExtras;
using namespace Qt3DCore;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QSlider* xMax;
    QSlider* yMax;
    QSlider* zMax;
    QSlider* tZad;
    QWidget *view_widget;
    QHBoxLayout *layoutX;
    QHBoxLayout *layoutY;
    QHBoxLayout *layoutZ;
    QHBoxLayout *layoutT;
    QHBoxLayout *layoutStep;
    QLineEdit *stepEdit;
    QLabel *xSymbol;
    QLabel *ySymbol;
    QLabel *zSymbol;
    QLabel *tSymbol;
    QLabel *valueX;
    QLabel *valueY;
    QLabel *valueZ;
    QLabel *valueT;
    QLabel *step;

    Scene *scene;

    void setQSliderRange(QSlider *slider, int min, int max);

private slots:
    //void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
