/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once
#include "views/MainWindow.h"
#include "presenters/AbstractPresenter.h"
#include "models/AbstractModel.h"


class ResizeModel;
class ResizeImageParametersWidget;

class ResizePresenter: public AbstractPresenter {
   public:
        ResizePresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget);
        virtual ~ResizePresenter();

    private:

    private slots:
        virtual void runModel();
        virtual void presentModelResults();
};
