#include "InpaintingPresenter.h"
#include "InpaintingParametersWidget.h"
#include "InpaintingModel.h"
#include "MainWindow.h"
#include "ImageConverter.h"
#include <thread>

InpaintingPresenter::InpaintingPresenter(MainWindow *parent, InpaintingModel *model, InpaintingParametersWidget *parametersWidget): AbstractPresenter(parent, model, parametersWidget)
{
}

InpaintingPresenter::~InpaintingPresenter() {
}

void InpaintingPresenter::runModel() {
    double size = parametersWidget->getSize();
    vpImage<vpRGBa> image = ImageConverter::qImageToVpImageRGBA(mainWindow->getSceneUp()->image());
    QImage mask = mainWindow->getSceneUp()->mask();
    model->setInput(image);
    model->setMask(ImageConverter::qImageToVpImageUCHAR(mask));
    std::thread first ([&] {model->run();} );
    first.detach();
}

void InpaintingPresenter::presentModelResults() {
        mainWindow->getSceneDown()->setImage(ImageConverter::vpImageRGBAToQImage(model->output()));
}
