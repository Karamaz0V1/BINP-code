#ifndef INPAINTINGPRESENTER_H
#define INPAINTINGPRESENTER_H
#pragma once

#include "AbstractPresenter.h"
class InpaintingModel;
class InpaintingParametersWidget;

class InpaintingPresenter : AbstractPresenter
{
Q_OBJECT
public:
    InpaintingPresenter(MainWindow *parent, InpaintingModel *model, InpaintingParametersWidget *parametersWidget);
    virtual ~InpaintingPresenter();
private slots:
    virtual void runModel();
    virtual void presentModelResults();
};

#endif // INPAINTINGPRESENTER_H
