#include <QtGui/QApplication>
#include "MainWindow.h"
#include "ResizePresenter.h"
#include "ResizeImageParametersWidget.h"
#include "ResizeModel.h"

MainWindow *w = NULL;

void addResize() {
    ResizeImageParametersWidget* view = new ResizeImageParametersWidget(w);
    w->addParameterWidget(view);
    ResizeModel* model = new ResizeModel();
    ResizePresenter* presenter = new ResizePresenter(w,model,view);
    w->setInteractive(true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow(0);
    addResize();
    w->show();

    return a.exec();
    delete w;
}
