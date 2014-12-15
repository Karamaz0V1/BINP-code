#include "views/ResizeImageParametersWidget.h"

ResizeImageParametersWidget::ResizeImageParametersWidget(QWidget *parent) :
    AbstractParametersWidget(parent)
{
    m_sbxScale=new QSpinBox(this);
    m_sbxScale->setRange(-1,1);
    m_sbxScale->setSingleStep(2);
    m_sbxScale->setValue(1);
    m_btnRun=new QPushButton("Run",this);
    QHBoxLayout *layoutSpin=new QHBoxLayout(this);
    layoutSpin->addWidget(new QLabel("Facteur d'echelle : "));
    layoutSpin->addWidget(m_sbxScale);
    QHBoxLayout *layoutBtn=new QHBoxLayout(this);
    layoutBtn->addWidget(m_btnRun);
    QVBoxLayout *layoutMain=new QVBoxLayout(this);
    layoutMain->addLayout(layoutSpin);
    layoutMain->addLayout(layoutBtn);
    this->setLayout(layoutMain);
    QObject::connect(m_btnRun,SIGNAL(clicked()),this,SIGNAL(runRequest()));
}

QString ResizeImageParametersWidget::title() const {

}

double ResizeImageParametersWidget::getFactor() const {
    return m_sbxScale->value();
}
