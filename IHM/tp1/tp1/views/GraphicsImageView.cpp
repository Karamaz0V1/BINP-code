#include "views/GraphicsImageView.h"
#include <iostream>

GraphicsImageView::GraphicsImageView(GraphicsImageScene *scene) :
    QGraphicsView(scene)
{
    m_scene=scene;
}

GraphicsImageScene* GraphicsImageView::scene() const {
    return m_scene;
}

void GraphicsImageView::mousePressEvent(QMouseEvent *e) {
    std::cout<<"AIE"<<std::endl;
    m_scene->paint(e->pos());
}

void GraphicsImageView::mouseMoveEvent(QMouseEvent *e) {
    //statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(e->pos().x()).arg(e->pos().y()));
    std::cout<<e->pos().x()<<":"<<e->pos().y()<<std::endl;
    m_scene->paint(e->pos());
}

void GraphicsImageView::wheelEvent(QWheelEvent *e) {
    int delta = e->delta();
    if(delta>0)
        this->scale(1.1,1.1);
    else
        this->scale(0.9,0.9);
}
