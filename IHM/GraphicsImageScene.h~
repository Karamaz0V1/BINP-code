/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __GRAPHICSIMAGESCENE_H__
#define __GRAPHICSIMAGESCENE_H__

class GraphicsImageScene: public QGraphicsScene {
    Q_OBJECT

    public:
        GraphicsImageScene(QObject *parent = NULL);
        virtual ~GraphicsImageScene();

    protected:
        QImage m_img;

    public:
        void setImage(const QImage &img);
        QImage image() const;
};

#endif /* __GRAPHICSIMAGESCENE_H__ */



