#include "mainwindow.h"
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      layoutX(new QHBoxLayout()),
      layoutY(new QHBoxLayout()),
      layoutZ(new QHBoxLayout()),
      layoutStep(new QHBoxLayout()),
      layoutSpeed(new QHBoxLayout()),
      layout(new QVBoxLayout(this)),
      xSymbol(new QLabel("x")),
      ySymbol(new QLabel("y")),
      zSymbol(new QLabel("z")),
      speedLabel(new QLabel("Speed")),
      step(new QPushButton("Step")),
      start(new QPushButton("Start")),
      stop(new QPushButton("Stop")),
      xStart(new QComboBox()),
      xFinish(new QComboBox()),
      yStart(new QComboBox()),
      yFinish(new QComboBox()),
      zStart(new QComboBox()),
      zFinish(new QComboBox()),
      speedCombobox(new QComboBox()),
      scene(new Scene)
{
    xStart->addItems(GetItems(xSize, 1));
    xStart->setCurrentIndex(1);
    xFinish->addItems(GetItems(xSize, 1));
    xFinish->setCurrentIndex(3);
    yStart->addItems(GetItems(ySize, 1));
    yStart->setCurrentIndex(4);
    yFinish->addItems(GetItems(ySize, 1));
    yFinish->setCurrentIndex(2);
    zStart->addItems(GetItems(zSize, 1));
    zStart->setCurrentIndex(1);
    zFinish->addItems(GetItems(zSize, 1));
    zFinish->setCurrentIndex(3);
    speedCombobox->addItem(QString::number(0.01f));
    speedCombobox->addItem(QString::number(0.05f));
    speedCombobox->addItem(QString::number(0.5f));
    speedCombobox->addItem(QString::number(1.0f));
    speedCombobox->setCurrentIndex(1);

    xStart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    xFinish->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    yStart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    yFinish->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    zStart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    zFinish->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    layoutX->addWidget(xSymbol);
    layoutX->addWidget(xStart);
    layoutX->addWidget(xFinish);
    layoutX->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    layoutY->addWidget(ySymbol);
    layoutY->addWidget(yStart);
    layoutY->addWidget(yFinish);
    layoutY->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    layoutZ->addWidget(zSymbol);
    layoutZ->addWidget(zStart);
    layoutZ->addWidget(zFinish);
    layoutZ->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    layoutStep->addWidget(step);
    layoutStep->addWidget(start);
    layoutStep->addWidget(stop);
    layoutSpeed->addWidget(speedLabel);
    layoutSpeed->addWidget(speedCombobox);
    layoutSpeed->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    view_widget = QWidget::createWindowContainer(&(scene->view));

    layout->addLayout(layoutX);
    layout->addLayout(layoutY);
    layout->addLayout(layoutZ);
    layout->addLayout(layoutSpeed);
    layout->addLayout(layoutStep);
    layout->addWidget(view_widget);

    view_widget->setMinimumSize(600, 800);
    setMinimumSize(800, 800);


    connect(start, &QPushButton::clicked, this, &MainWindow::StartButtonClicked);
    connect(stop, &QPushButton::clicked, this, &MainWindow::stopClicked);
    connect(step, &QPushButton::clicked, this, &MainWindow::stepClicked);
}

QStringList MainWindow::GetItems(int max, int min)
{
    QStringList list;
    for(int i = min; i <= max; ++i)
        list.append(QString::number(i));

    return list;
}

void MainWindow::StartButtonClicked()
{
    if (scene->knife->knifeTransform->translation() != scene->knife->basePosition)
        stopClicked();
    scene->discretShift = speedCombobox->currentText().toFloat();
    scene->setAnimationBounds(xStart->currentText().toInt(),
                              xFinish->currentText().toInt(),
                              yStart->currentText().toInt(),
                              yFinish->currentText().toInt(),
                              zStart->currentText().toInt(),
                              zFinish->currentText().toInt());
    scene->startAutoAnimation();

}

void MainWindow::stepClicked()
{
    scene->discretShift = speedCombobox->currentText().toFloat();
    if (scene->isAutoAnimationNow) {
        scene->tmr->stop();
        scene->isStepAnimationNow = true;
        scene->isAutoAnimationNow = false;
    }

    if (!scene->isStepAnimationNow)
        scene->setAnimationBounds(xStart->currentText().toInt(),
                                  xFinish->currentText().toInt(),
                                  yStart->currentText().toInt(),
                                  yFinish->currentText().toInt(),
                                  zStart->currentText().toInt(),
                                  zFinish->currentText().toInt());
    scene->startStepAnimation();

}

void MainWindow::stopClicked() {
    //emit(scene->stopTmr());
    scene->tmr->stop();
    scene->knife->knifeTransform->setTranslation(scene->knife->basePosition);
    scene->discretShift = 0;
    scene->elapsedSteps = 0;
    scene->isStepAnimationNow = false;
    scene->isAutoAnimationNow = false;
    //std::cout << scene->knife->knifeTransform->translation().x() << " " << scene->knife->knifeTransform->translation().z() << " " <<scene->knife->knifeTransform->translation().y() << std::endl;
    for (int i = 0; i < scene->animationParts.size(); i++) {
        delete scene->animationParts[i];
        scene->animationParts.erase(scene->animationParts.begin());
        i--;
    }
    scene->currentPart = 0;
    for (int i = 0; i < scene->billet->billet.size(); i++) {
        for (int j = 0; j < scene->billet->billet[i].size(); j++)
            for (int k = 0; k < scene->billet->billet[i][j].size(); k++)
                scene->billet->billet[i][j][k]->setEnabled(true);
    }


}

void MainWindow::setQSliderRange(QSlider *slider, int min, int max) {
    slider->setMinimum(min);
    slider->setMaximum(max);
}

