/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

#include "presenters/AbstractPresenter.h"
#include "models/AbstractModel.h"

class ResizePresenter: public AbstractPresenter {
   public:
        //TODO ResizeModel && Widget
        ResizePresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget);
        //TODO implementer dans cpp
        virtual ~ResizePresenter();

    private:

    private slots:
        virtual void runModel();
        virtual void presentModelResults();
};
