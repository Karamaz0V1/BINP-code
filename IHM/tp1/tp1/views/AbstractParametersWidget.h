/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

#include <QObject>
#include <QWidget>

class AbstractParametersWidget: public QWidget {
    Q_OBJECT
    public:
        AbstractParametersWidget(QWidget *parent = NULL);
        virtual ~AbstractParametersWidget();

        virtual QString title() const = 0;

    signals:
        void runRequest();

    protected:
        //TODO

   private:
        //TODO
};
