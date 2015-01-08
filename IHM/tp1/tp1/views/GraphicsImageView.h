#ifndef GRAPHICSIMAGEVIEW_H
#define GRAPHICSIMAGEVIEW_H

#include <QGraphicsView>
#include "views/GraphicsImageScene.h"
#include <QWheelEvent>

class GraphicsImageView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsImageView(GraphicsImageScene *scene);

protected:
    GraphicsImageScene * m_scene;
public :
    virtual GraphicsImageScene* scene() const;
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    
signals:
    
public slots:
    
};

#endif // GRAPHICSIMAGEVIEW_H
