/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

class MainWindow;
class AbstractModel;
class AbstractParametersWidget;

#include <QObject>

class AbstractPresenter: public QObject {
    Q_OBJECT
    public:
        AbstractPresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget);
        virtual ~AbstractPresenter();

    protected:
        MainWindow * parent;
        AbstractModel * model;
        AbstractParametersWidget * parametersWidget;
        
    private:

    private slots:
        virtual void runModel() = 0;
        virtual void presentModelResults() = 0;

};
