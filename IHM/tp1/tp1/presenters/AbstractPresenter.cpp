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
    QObject::connect(model,SIGNAL(success()), this,SLOT(presentModelResults()));
    QObject::connect(parametersWidget,SIGNAL(runRequest()), this,SLOT(runModel()));
}

AbstractPresenter::~AbstractPresenter() {
}
