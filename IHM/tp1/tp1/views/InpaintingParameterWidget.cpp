#include "InpaintingParameterWidget.h"

InpaintingParameterWidget::InpaintingParameterWidget(QWidget *parent) :
    AbstractParametersWidget(parent)
{
    m_btnCercle=new QPushButton("Cercle",this);
    m_btnCarre=new QPushButton("Carre",this);
    m_btnRun=new QPushButton("RUN",this);
    m_sldTailleBrush=new QSlider(this);
    m_sldTailleBrush->setValue(0);
    QVBoxLayout *layoutSlider=new QVBoxLayout(this);
    layoutSlider->addWidget(new QLabel("Taille de la brosse : "));
    layoutSlider->addWidget(m_sldTailleBrush);
    QHBoxLayout *layoutBtnShape=new QHBoxLayout(this);
    layoutBtnShape->addWidget(m_btnCercle);
    layoutBtnShape->addWidget(m_btnCarre);
    QVBoxLayout *layoutMain=new QVBoxLayout(this);
    layoutMain->addLayout(layoutBtnShape);
    layoutMain->addLayout(layoutSlider);
    layoutMain->addWidget(m_btnRun);
    this->setLayout(layoutMain);
    QObject::connect(m_btnRun,SIGNAL(clicked()),this,SIGNAL(runRequest()));

}


QString InpaintingParameterWidget::title() const {
    return "Inpainting";
}

double InpaintingParameterWidget::getSize() const {
    return m_sldTailleBrush->value();
}

double InpaintingParameterWidget::getFactor() const {
    return 0;
}
