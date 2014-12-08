#include <QtGui/QApplication>
#include "views/MainWindow.h"
#include "views/ResizeImageParametersWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ResizeImageParametersWidget* view = new ResizeImageParametersWidget(&w);
    w.addParameterWidget(view);
    w.show();
    return a.exec();
}
