#include <QtGui/QApplication>
#include "MainWindow.h"
//#include "views/ResizeImageParametersWidget.h"
#include "ResizePresenter.h"
#include "ResizeImageParametersWidget.h"
#include "ResizeModel.h"

MainWindow *w = NULL;

void addResize() {
    ResizeImageParametersWidget* view = new ResizeImageParametersWidget(w);
    w->addParameterWidget(view);
    ResizeModel* model = new ResizeModel();
    ResizePresenter* presenter = new ResizePresenter(w,model,view);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow(0);
    //ResizeImageParametersWidget* view = new ResizeImageParametersWidget(&w);
    //w.addParameterWidget(view);
    addResize();
    w->show();

    delete w;
    return a.exec();
}
