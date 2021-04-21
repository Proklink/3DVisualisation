#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      xMax(new QSlider(Qt::Horizontal, this)),
      yMax(new QSlider(Qt::Horizontal, this)),
      zMax(new QSlider(Qt::Horizontal, this)),
      tZad(new QSlider(Qt::Horizontal, this)),
      layoutX(new QHBoxLayout()),
      layoutY(new QHBoxLayout()),
      layoutZ(new QHBoxLayout()),
      layoutT(new QHBoxLayout()),
      layoutStep(new QHBoxLayout()),
      stepEdit(new QLineEdit("1")),
      xSymbol(new QLabel("x")),
      ySymbol(new QLabel("y")),
      zSymbol(new QLabel("z")),
      tSymbol(new QLabel("t")),
      valueX(new QLabel("0")),
      valueY(new QLabel("0")),
      valueZ(new QLabel("0")),
      valueT(new QLabel("0")),
      step(new QLabel("Step:"))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setQSliderRange(xMax, 3, 20);
    setQSliderRange(yMax, 1, 4);
    setQSliderRange(zMax, 1, 2);
    setQSliderRange(tZad, 1, 30000);

    stepEdit->setValidator(new QIntValidator(0, 99, this));

    layoutX->addWidget(xSymbol);
    layoutX->addWidget(xMax);
    layoutX->addWidget(valueX);
    layoutY->addWidget(ySymbol);
    layoutY->addWidget(yMax);
    layoutY->addWidget(valueY);
    layoutZ->addWidget(zSymbol);
    layoutZ->addWidget(zMax);
    layoutZ->addWidget(valueZ);
    layoutT->addWidget(tSymbol);
    layoutT->addWidget(tZad);
    layoutT->addWidget(valueT);
    layoutStep->addWidget(step);
    layoutStep->addWidget(stepEdit);

    connect(xMax, &QSlider::valueChanged,
            valueX, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(yMax, &QSlider::valueChanged,
            valueY, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(zMax, &QSlider::valueChanged,
            valueZ, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(tZad, &QSlider::valueChanged,
            valueT, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    scene = new Scene();
    view_widget = QWidget::createWindowContainer(&(scene->view));

    layout->addLayout(layoutX);
    layout->addLayout(layoutY);
    layout->addLayout(layoutZ);
    layout->addLayout(layoutT);
    layout->addLayout(layoutStep);
    layout->addWidget(view_widget);

    view_widget->setMinimumSize(600, 800);
    setMinimumSize(800, 800);

    scene->startTestAnimation(2, 5, 5, 3, 2, 5);
}

void MainWindow::setQSliderRange(QSlider *slider, int min, int max) {
    slider->setMinimum(min);
    slider->setMaximum(max);
}

//void MainWindow::keyPressEvent(QKeyEvent *event)
//{

//    if (event->key() == 1055)
//    {
//        std::cout << "Animation has started" << std::endl;
//        scene->startTestAnimation();
//    }

//}
