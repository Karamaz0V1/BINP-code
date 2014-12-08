#include "GraphicsImageView.h"

GraphicsImageView::GraphicsImageView(GraphicsImageScene *scene) :
    QGraphicsView(scene)
{
    m_scene=scene;
}

GraphicsImageScene* GraphicsImageView::scene() const {
    return m_scene;
}

void GraphicsImageView::wheelEvent(QWheelEvent *e) {
    int delta = e->delta();
    if(delta>0)
        this->scale(1.1,1.1);
    else
        this->scale(0.9,0.9);
}
