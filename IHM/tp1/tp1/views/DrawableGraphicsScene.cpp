#include "DrawableGraphicsScene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QPixmap>

class DrawableGraphicsScenePrivate
{
public:
    QGraphicsPathItem *maskItem;
    QGraphicsPathItem *brushItem;
    QImage qimage;

    bool isInteractive;
    bool brusVisibility;
    unsigned int brushSize;
    DrawableGraphicsScene::BrushShape brushShape;
    QPainterPath brushPainterPath;

    void updateBrushPainterPath()
    {
        brushPainterPath = QPainterPath();
        switch(brushShape)
        {
            case DrawableGraphicsScene::CIRCLE:
                brushPainterPath.addEllipse(QRectF(0, 0, brushSize, brushSize));
                break;
            case DrawableGraphicsScene::SQUARE:
                brushPainterPath.addRect(QRectF(0, 0, brushSize, brushSize));
                break;
            default:
                break;
        }
    }
};

DrawableGraphicsScene::DrawableGraphicsScene(QObject *parent):
    QGraphicsScene(parent), d(new DrawableGraphicsScenePrivate)
{
    // there will be intialized when reset() will be called.
    d->maskItem = NULL;
    d->brushItem = NULL;

    this->reset();
    this->setInteractive(false);
}

DrawableGraphicsScene::~DrawableGraphicsScene()
{
    delete d->maskItem;
}

void DrawableGraphicsScene::setInteractive(bool isInteractive)
{
    d->isInteractive = isInteractive;
}

bool DrawableGraphicsScene::isInteractive() const
{
    return d->isInteractive;
}

void DrawableGraphicsScene::reset()
{
    // first clear the scene
    delete d->maskItem;
    delete d->brushItem;
    this->clear();

    d->qimage  = QImage();

    // add new empty mask and cursor items
    d->maskItem = new QGraphicsPathItem;
    this->addItem(d->maskItem);
    d->maskItem->setBrush(QBrush(QColor(255, 0, 0, 64)));
    d->maskItem->setPen(Qt::NoPen);

    d->brushItem = new QGraphicsPathItem;
    d->brushItem->setBrush(QBrush(QColor(0, 0, 255, 64)));
    d->brushItem->setPen(Qt::NoPen);
    this->addItem(d->brushItem);

    // so cursor item appears at the top of maskItem
    d->maskItem->setZValue(d->brushItem->zValue() - 1);
}

void DrawableGraphicsScene::setImage(const QImage &img)
{
    this->reset();

    // recompute the scene size to match the size of the qimage,
    // otherwise the alignment of the scene in the graphicsView is lost.
    this->setSceneRect(0, 0, img.width(), img.height());
    QGraphicsPixmapItem *pixmapItem = this->addPixmap(QPixmap::fromImage(img));

    // so the mask always appears at the top of the qimage.
    pixmapItem->setZValue(d->maskItem->zValue() - 1);
    d->qimage = img;
}

QImage DrawableGraphicsScene::image() const
{
    return d->qimage;
}

QImage DrawableGraphicsScene::mask() const
{
    qDebug() << "Start mask construction...";

    // draw the mask path in a QPixmap thanks to a QPainter.
    QPixmap maskPixmap(d->qimage.size());
    QPainter painter;
    painter.begin(&maskPixmap);
    painter.setBrush(QBrush(QColor(255, 255, 255, 255)));
    painter.drawPath(d->maskItem->path());
    painter.end();

    qDebug() << "End mask construction...";
    return maskPixmap.toImage();
}

void DrawableGraphicsScene::setBrushVisibility(bool visibility)
{
    d->brushItem->setVisible(visibility);
}

bool DrawableGraphicsScene::brushVisibility() const
{
    return d->brusVisibility;
}

void DrawableGraphicsScene::setBrushShape(BrushShape shape)
{
    d->brushShape = shape;
    d->updateBrushPainterPath();
}

DrawableGraphicsScene::BrushShape DrawableGraphicsScene::brushShape() const
{
    return d->brushShape;
}

void DrawableGraphicsScene::setBrushSize(unsigned int size)
{
    d->brushSize = size;
    d->updateBrushPainterPath();
}

unsigned int DrawableGraphicsScene::brushSize() const
{
    return d->brushSize;
}

void DrawableGraphicsScene::redrawBrush(const QPointF &position)
{
    QPainterPath cursorPath = d->brushPainterPath.translated(position);
    d->brushItem->setPath(cursorPath);
}


void DrawableGraphicsScene::paint(const QPointF &position)
{
    QPainterPath maskPath = d->maskItem->path();
    QPainterPath path = d->brushPainterPath.translated(position);
    maskPath += path;
    d->maskItem->setPath(maskPath);
}

void DrawableGraphicsScene::erase(const QPointF &position)
{
    QPainterPath maskPath = d->maskItem->path();
    QPainterPath path = d->brushPainterPath.translated(position);
    maskPath -= path;
    d->maskItem->setPath(maskPath);
}
