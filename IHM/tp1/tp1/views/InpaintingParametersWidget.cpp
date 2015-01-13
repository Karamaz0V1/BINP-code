#include "InpaintingParametersWidget.h"

InpaintingParametersWidget::InpaintingParametersWidget(QWidget *parent) :
    AbstractParametersWidget(parent)
{
    m_btnCercle=new QPushButton("Cercle",this);
    m_btnCarre=new QPushButton("Carre",this);
    m_btnRun=new QPushButton("RUN",this);
    m_sldTailleBrush=new QSlider(this);
    m_sldTailleBrush->setValue(0);
    m_sldTailleBrush->setOrientation(Qt::Horizontal);
    QVBoxLayout *layoutSlider=new QVBoxLayout();
    layoutSlider->addWidget(new QLabel("Taille de la brosse : "));
    layoutSlider->addWidget(m_sldTailleBrush);
    QHBoxLayout *layoutBtnShape=new QHBoxLayout();
    layoutBtnShape->addWidget(m_btnCercle);
    layoutBtnShape->addWidget(m_btnCarre);
    QVBoxLayout *layoutMain=new QVBoxLayout(this);
    layoutMain->addLayout(layoutBtnShape);
    layoutMain->addLayout(layoutSlider);
    layoutMain->addWidget(m_btnRun);
    this->setLayout(layoutMain);
    QObject::connect(m_btnRun,SIGNAL(clicked()),this,SIGNAL(runRequest()));

}


QString InpaintingParametersWidget::title() const {
    return "Inpainting";
}

double InpaintingParametersWidget::getSize() const {
    return m_sldTailleBrush->value();
}

double InpaintingParametersWidget::getFactor() const {
    return 0;
}
