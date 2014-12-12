/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "ResizePresenter.h"

ResizePresenter::ResizePresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget) : AbstractPresenter(parent, model, parametersWidget) {

}

void ResizePresenter::runModel() {
    model->run();
}

void ResizePresenter::presentModelResults() {

}
