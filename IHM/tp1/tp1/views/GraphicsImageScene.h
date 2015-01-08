#ifndef GRAPHICSIMAGESCENE_H
#define GRAPHICSIMAGESCENE_H

//#include <QGraphicsScene>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QImage>
#include <QMouseEvent>
#include "DrawableGraphicsScene.h"

class GraphicsImageScene : public DrawableGraphicsScene
{
    Q_OBJECT
public:
    GraphicsImageScene(QWidget *window,QObject *parent = 0);
    virtual ~GraphicsImageScene();

protected:
    QImage m_image;
private:
    QWidget *m_window;

public:
    void paint(const QPointF &position);
    void setInteractive(bool intercative);
    
signals:
    
public slots:
    void printImage();
    void saveImage();
    
};

#endif // GRAPHICSIMAGESCENE_H
