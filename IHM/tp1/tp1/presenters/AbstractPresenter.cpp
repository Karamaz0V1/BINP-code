/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "AbstractPresenter.h"
#include "views/AbstractParametersWidget.h"
#include "models/AbstractModel.h"

AbstractPresenter::AbstractPresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget) : mainWindow(parent), model(model), parametersWidget(parametersWidget) {
    QObject::connect(model,SIGNAL(model->success()), this,SLOT(this->presentModelResults()));
    QObject::connect(parametersWidget,SIGNAL(parametersWidget->runRequest()), this,SLOT(this->runModel()));
}

AbstractPresenter::~AbstractPresenter() {
}
