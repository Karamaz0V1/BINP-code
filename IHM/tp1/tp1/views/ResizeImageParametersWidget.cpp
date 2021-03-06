#include "ResizeImageParametersWidget.h"

ResizeImageParametersWidget::ResizeImageParametersWidget(QWidget *parent) :
    AbstractParametersWidget(parent)
{
    m_sbxScale=new QSpinBox(this);
    m_sbxScale->setRange(-10,10);
    m_sbxScale->setSingleStep(1);
    m_sbxScale->setValue(1);
    m_btnRun=new QPushButton("Run",this);
    QHBoxLayout *layoutSpin=new QHBoxLayout();
    layoutSpin->addWidget(new QLabel("Facteur d'echelle : "));
    layoutSpin->addWidget(m_sbxScale);
    QHBoxLayout *layoutBtn=new QHBoxLayout();
    layoutBtn->addWidget(m_btnRun);
    QVBoxLayout *layoutMain=new QVBoxLayout(this);
    layoutMain->addLayout(layoutSpin);
    layoutMain->addLayout(layoutBtn);
    this->setLayout(layoutMain);
    QObject::connect(m_btnRun,SIGNAL(clicked()),this,SIGNAL(runRequest()));
}

QString ResizeImageParametersWidget::title() const {
    return "Resize Image";
}

double ResizeImageParametersWidget::getFactor() const {
    return m_sbxScale->value();
}

double ResizeImageParametersWidget::getSize() const {
    return 0;
}
