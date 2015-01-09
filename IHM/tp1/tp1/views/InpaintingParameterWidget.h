#ifndef INPAINTINGPARAMETERWIDGET_H
#define INPAINTINGPARAMETERWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "AbstractParametersWidget.h"
class InpaintingParameterWidget : public AbstractParametersWidget
{
    Q_OBJECT
private:
    QPushButton *m_btnCercle;
    QPushButton *m_btnCarre;
    QSlider *m_sldTailleBrush;
    QPushButton *m_btnRun;
public:
    explicit InpaintingParameterWidget(QWidget *parent = 0);
    QString title() const;
    double getFactor() const;
    double getSize() const;
signals:
    void runRequest();
};

#endif // INPAINTINGPARAMETERWIDGET_H
