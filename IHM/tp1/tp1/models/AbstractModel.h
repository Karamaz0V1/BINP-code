/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#pragma once

#include <QObject>

class AbstractModel: public QObject {
    Q_OBJECT
    public:
        AbstractModel(QObject *parent = NULL);
        virtual ~AbstractModel();

        virtual void run() = 0;

    signals:
        void success();
};
