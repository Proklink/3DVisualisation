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
    xStart->addItems(GetItems(xSize, 0));
    xFinish->addItems(GetItems(xSize, 0));
    yStart->addItems(GetItems(ySize, 0));
    yFinish->addItems(GetItems(ySize, 0));
    zStart->addItems(GetItems(zSize, 0));
    zFinish->addItems(GetItems(zSize, 0));
    speedCombobox->addItem(QString::number(0.05f));
    speedCombobox->addItem(QString::number(0.01f));
    speedCombobox->addItem(QString::number(1.0f));

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

    connect(start, &QPushButton::clicked, this, &MainWindow::StartButtonClicked);

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
    scene->startTestAnimation(xStart->currentText().toInt(),
                              xFinish->currentText().toInt(),
                              yStart->currentText().toInt(),
                              yFinish->currentText().toInt(),
                              zStart->currentText().toInt(),
                              zFinish->currentText().toInt());
    scene->discretShift = speedCombobox->currentText().toInt();
}

void MainWindow::stopClicked() {
    //emit signal for timer
    scene->knife->knifeTransform->setTranslation(scene->knife->basePosition);
}

void MainWindow::setQSliderRange(QSlider *slider, int min, int max) {
    slider->setMinimum(min);
    slider->setMaximum(max);
}

