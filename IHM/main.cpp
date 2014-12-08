/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <QWidget>
#include <QApplication>
#include "views/MainWindow.h"

int main( int argc, char* argv[] )
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    MainWindow *mainWindow = new MainWindow();

    mainWindow->show();
    int code = app.exec();
    delete window;
    return 0;
}


