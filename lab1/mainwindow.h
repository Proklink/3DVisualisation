#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLayout>
#include <QRadioButton>
#include <Qt3DExtras>
#include <QLabel>
#include <QIntValidator>
#include <QKeyEvent>
#include "scene.h"
#include "Storage.h"

using namespace Qt3DExtras;
using namespace Qt3DCore;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget *view_widget;
    QHBoxLayout *layoutX;
    QHBoxLayout *layoutY;
    QHBoxLayout *layoutZ;
    QHBoxLayout *layoutStep;
    QHBoxLayout *layoutSpeed;
    QVBoxLayout *layout;
    QLabel *xSymbol;
    QLabel *ySymbol;
    QLabel *zSymbol;
    QLabel *speedLabel;
    QPushButton *step;
    QPushButton *start;
    QPushButton *stop;
    QComboBox *xStart;
    QComboBox *xFinish;
    QComboBox *yStart;
    QComboBox *yFinish;
    QComboBox *zStart;
    QComboBox *zFinish;
    QComboBox *speedCombobox;

    Scene *scene;

    void setQSliderRange(QSlider *slider, int min, int max);
private:
    QStringList GetItems(int max, int min);

private slots:
    void StartButtonClicked();
    void stopClicked();
    void stepClicked();
};

#endif // MAINWINDOW_H
