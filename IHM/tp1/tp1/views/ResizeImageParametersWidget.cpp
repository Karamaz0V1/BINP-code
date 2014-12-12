#include "views/ResizeImageParametersWidget.h"

ResizeImageParametersWidget::ResizeImageParametersWidget(QWidget *parent) :
    QWidget(parent)
{
    m_sbxScale=new QSpinBox(this);
    m_sbxScale->setRange(0,20);
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
}