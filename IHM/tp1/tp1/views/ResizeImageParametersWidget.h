#ifndef RESIZEIMAGEPARAMETERSWIDGET_H
#define RESIZEIMAGEPARAMETERSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ResizeImageParametersWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *m_sbxScale;
    QPushButton *m_btnRun;
public:
    explicit ResizeImageParametersWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // RESIZEIMAGEPARAMETERSWIDGET_H
