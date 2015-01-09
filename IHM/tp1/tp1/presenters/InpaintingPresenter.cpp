#include "InpaintingPresenter.h"
#include "InpaintingParametersWidget.h"
#include "InpaintingModel.h"
#include "MainWindow.h"
#include "ImageConverter.h"
InpaintingPresenter::InpaintingPresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget): AbstractPresenter(parent, model, parametersWidget)
{
}

InpaintingPresenter::~InpaintingPresenter() {
}

void InpaintingPresenter::runModel() {
    double size = parametersWidget->getSize();
    vpImage<vpRGBa> image = ImageConverter::qImageToVpImageRGBA(mainWindow->getSceneUp()->image());
    QImage mask = mainWindow->getSceneUp()->mask();
    model->setInput(image);
    model->setMask(mask);
    model->run();
}

void InpaintingPresenter::presentModelResults() {
        mainWindow->getSceneDown()->setImage(ImageConverter::vpImageRGBAToQImage(model->output()));
}
