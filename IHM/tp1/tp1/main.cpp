#include <QtGui/QApplication>
#include "MainWindow.h"
#include "ResizePresenter.h"
#include "ResizeImageParametersWidget.h"
#include "ResizeModel.h"
#include "InpaintingParametersWidget.h"
#include "InpaintingModel.h"
#include "InpaintingPresenter.h"

MainWindow *w = NULL;

void addResize() {
    ResizeImageParametersWidget* view = new ResizeImageParametersWidget(w);
    w->addParameterWidget(view);
    ResizeModel* model = new ResizeModel();
    ResizePresenter* presenter = new ResizePresenter(w,model,view);
    //w->setInteractive(true);
}

void addInpainting() {
    InpaintingParametersWidget* view = new InpaintingParametersWidget(w);
    w->addParameterWidget(view);
    InpaintingModel* model = new InpaintingModel();
    InpaintingPresenter* presenter = new InpaintingPresenter(w,model,view);
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
