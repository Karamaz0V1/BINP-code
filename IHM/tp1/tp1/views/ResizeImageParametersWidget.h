#ifndef RESIZEIMAGEPARAMETERSWIDGET_H
#define RESIZEIMAGEPARAMETERSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "AbstractParametersWidget.h"

class ResizeImageParametersWidget : public AbstractParametersWidget
{
    Q_OBJECT
private:
    QSpinBox *m_sbxScale;
    QPushButton *m_btnRun;
public:
    explicit ResizeImageParametersWidget(QWidget *parent = 0);
    QString title() const;
    double getFactor() const;
    double getSize() const;

signals:
    void runRequest();
public slots:
    
};

#endif // RESIZEIMAGEPARAMETERSWIDGET_H
