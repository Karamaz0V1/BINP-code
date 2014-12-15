/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "ResizePresenter.h"
#include "views/ResizeImageParametersWidget.h"
#include "models/ResizeModel.h"

ResizePresenter::ResizePresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget) : AbstractPresenter(parent, model, parametersWidget) {

}

ResizePresenter::~ResizePresenter() {
}

void ResizePresenter::runModel() {
    model->run();
}

void ResizePresenter::presentModelResults() {
        parent->getSceneDown()->setImage(model->output());
}
