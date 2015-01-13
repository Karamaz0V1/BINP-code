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
        if(e->buttons()==Qt::LeftButton)
            m_scene->paint(e->pos());
        else if(e->buttons()==Qt::RightButton)
            m_scene->erase(e->pos());
}

void GraphicsImageView::mouseMoveEvent(QMouseEvent *e) {
        if(e->buttons()==Qt::LeftButton)
            m_scene->paint(e->pos());
        else if(e->buttons()==Qt::RightButton)
            m_scene->erase(e->pos());
}

void GraphicsImageView::wheelEvent(QWheelEvent *e) {
    int delta = e->delta();
    if(delta>0)
        this->scale(1.1,1.1);
    else
        this->scale(0.9,0.9);
}
