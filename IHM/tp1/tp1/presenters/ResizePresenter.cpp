/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "ResizePresenter.h"
#include "ResizeImageParametersWidget.h"
#include "ResizeModel.h"
#include "MainWindow.h"
#include "ImageConverter.h"

ResizePresenter::ResizePresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget) : AbstractPresenter(parent, model, parametersWidget) {

}

ResizePresenter::~ResizePresenter() {
}

void ResizePresenter::runModel() {
    double factor = parametersWidget->getFactor();
    vpImage<vpRGBa> image = ImageConverter::qImageToVpImageRGBA(mainWindow->getSceneUp()->image());
    model->run(image,factor);
}

void ResizePresenter::presentModelResults() {
        mainWindow->getSceneDown()->setImage(ImageConverter::vpImageRGBAToQImage(model->output()));
}
