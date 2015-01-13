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

        virtual void run() = 0;

        virtual vpImage<vpRGBa> output() const = 0;

        virtual void setInput(const vpImage<vpRGBa> &img) = 0;

        virtual void setScaleFactor(const double & factor) = 0;

        virtual void setMask(const vpImage<unsigned char> &img) = 0;

    signals:
        void success();
};
