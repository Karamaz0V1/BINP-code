/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

#include <QObject>
#include <visp/vpImage.h>

class AbstractModel: public QObject {
    Q_OBJECT
    public:
        AbstractModel(QObject *parent = NULL);
        virtual ~AbstractModel();

        virtual void run(vpImage<vpRGBa> image,double factor) = 0;

        virtual vpImage<vpRGBa> output() = 0;

    signals:
        void success();
};
