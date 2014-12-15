/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "AbstractPresenter.h"

AbstractPresenter::AbstractPresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget) : model(model), parametersWidget(parametersWidget) {
}

AbstractPresenter::~AbstractPresenter() {
}
