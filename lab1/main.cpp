#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
//    Scene *scene = new Scene();

//    scene->view.show();


    return app.exec();
}

