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
    void wheelEvent(QWheelEvent *e);
    
signals:
    
public slots:
    
};

#endif // GRAPHICSIMAGEVIEW_H
