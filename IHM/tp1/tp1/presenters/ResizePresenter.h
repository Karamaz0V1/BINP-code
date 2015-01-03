/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

#include "AbstractPresenter.h"

class ResizeModel;
class ResizeImageParametersWidget;

class ResizePresenter: public AbstractPresenter
{
    Q_OBJECT

   public:
        ResizePresenter(MainWindow *parent, ResizeModel *model, ResizeImageParametersWidget *parametersWidget);
        virtual ~ResizePresenter();

    private:

    private slots:
        virtual void runModel();
        virtual void presentModelResults();
};
