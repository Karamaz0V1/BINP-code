#pragma once

#include <QGraphicsScene>

class QPainterPath;
class QPointF;


class DrawableGraphicsScenePrivate;
class DrawableGraphicsScene: public QGraphicsScene
{
    Q_OBJECT
public:
    DrawableGraphicsScene(QObject *parent = NULL);
    virtual ~DrawableGraphicsScene();

public:
    /**
     * Set the image to display in ths scene.
     */
    void setImage(const QImage &img);
    /**
     * Return the QImage currently displayed in the scene,
     * If there is no image beeing displayed it returns an empty QImage
     */
    QImage image() const;
    /**
     * Return a binary QImage (background is 0, foreground is 255), where
     * the forground is what the user have painted on the scene.
     */
    QImage mask() const;

public:
    /**
     * The diferent possible shape that can be used to paint
     * with the brush.
     */
    enum BrushShape
    {
        CIRCLE,
        SQUARE
    };

    /**
     * Set the size of the Brush used to paint.
     */
    void setBrushSize(unsigned int size);
    unsigned int brushSize() const;
    /**
     * Set the shape of the Brush used to paint.
     */
    void setBrushShape(BrushShape shape);
    BrushShape brushShape() const;
    /**
     * set if the Brush is visible or not
     */
    void setBrushVisibility(bool visibility);
    bool brushVisibility() const;

public:
    /**
     * Set if the scene is intercative or not
     * The user can paint on the scene only if it is interactive
     */
    void setInteractive(bool intercative);
    bool isInteractive() const;

protected:
    /**
     * Redraw a brush on the scene, at the given position.
     */
    void redrawBrush(const QPointF &position);
    /**
     * Paint on the scene at the given position.
     */
    void paint(const QPointF &position);
    /**
     * Unpaint at the given position.
     */
    void erase(const QPointF &position);

private:
    void reset();
    // Pointer to implementation:
    DrawableGraphicsScenePrivate *d;
};
