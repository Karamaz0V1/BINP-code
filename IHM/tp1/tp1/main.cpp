#include <QtGui/QApplication>
#include "MainWindow.h"
#include "ResizePresenter.h"
#include "ResizeImageParametersWidget.h"
#include "ResizeModel.h"
#include "InpaintingParameterWidget.h"

MainWindow *w = NULL;

void addResize() {
    ResizeImageParametersWidget* view = new ResizeImageParametersWidget(w);
    w->addParameterWidget(view);
    ResizeModel* model = new ResizeModel();
    ResizePresenter* presenter = new ResizePresenter(w,model,view);
    //w->setInteractive(true);
}

void addInpainting() {
    InpaintingParameterWidget* view = new InpaintingParameterWidget(w);
    w->addParameterWidget(view);
    //InpaintingModel* model = new InpaintingModel();
    //InpaintingPresenter* presenter = new InpaintingPresenter(w,model,view);
    w->setInteractive(true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow(0);
    addResize();
    addInpainting();
    w->show();

    return a.exec();
    delete w;
}
