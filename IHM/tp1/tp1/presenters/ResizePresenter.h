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
//#include "views/ResizeImageParametersWidget.h"

class ResizeModel;
class ResizeImageParametersWidget;

class ResizePresenter: public AbstractPresenter {
   public:
        //TODO ResizeModel && Widget
        ResizePresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget);
        virtual ~ResizePresenter();

    private:

    private slots:
        virtual void runModel();
        virtual void presentModelResults();
};
