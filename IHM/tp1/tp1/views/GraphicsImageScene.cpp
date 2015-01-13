#include "views/GraphicsImageScene.h"
#include "DrawableGraphicsScene.h"

#include <iostream>

GraphicsImageScene::GraphicsImageScene(QWidget *window, QObject *parent) :
    DrawableGraphicsScene(parent)
{
    m_window=window;
}

GraphicsImageScene::~GraphicsImageScene() {

}

void GraphicsImageScene::printImage() {
    QWidget *window = m_window;
    QString title = "Ouvrir";
    QString dir = "~";
    QString filters = tr("Images (*.png *.xpm *.jpg *.bnp *.pnm *.pbm *.pgm)");
    QFileDialog *file = new QFileDialog(window,title,dir,filters);
    QStringList chosenFile;
    file->setFileMode(QFileDialog::ExistingFile);
    file->show();
    if(file->exec())
        chosenFile=file->selectedFiles();
    QString fileName=chosenFile.first();
    QImage* image = new QImage(fileName);
    setImage(*image);
}

void GraphicsImageScene::paint(const QPointF &position) {
    DrawableGraphicsScene::setBrushSize(10);
    DrawableGraphicsScene::setBrushShape(DrawableGraphicsScene::CIRCLE);
    DrawableGraphicsScene::setBrushVisibility(true);
    DrawableGraphicsScene::paint(position);
    DrawableGraphicsScene::redrawBrush(position);
}

void GraphicsImageScene::erase(const QPointF &position) {
    DrawableGraphicsScene::setBrushSize(10);
    DrawableGraphicsScene::setBrushShape(DrawableGraphicsScene::CIRCLE);
    DrawableGraphicsScene::setBrushVisibility(true);
    DrawableGraphicsScene::erase(position);
    DrawableGraphicsScene::redrawBrush(position);
}

void GraphicsImageScene::setInteractive(bool intercative) {
    DrawableGraphicsScene::setInteractive(intercative);
}

void GraphicsImageScene::saveImage() {
    QWidget *window = m_window;
    QString title = "Enregistrer";
    QString dir = "~";
    QString filters = tr("Images (*.png *.xpm *.jpg *.bnp)");
    QFileDialog *file = new QFileDialog(window,title,dir,filters);
    QStringList chosenFile;
    file->setFileMode(QFileDialog::AnyFile);
    file->show();
    QString fileName;
    QMessageBox* error = new QMessageBox();
    QString text;
    if(file->exec()) {
        chosenFile=file->selectedFiles();
        fileName=chosenFile.first();
        if(!image().save(fileName))
            text="L'image n'a pas ete sauvegardee";
        else
            text="L'image a bien ete sauvegardee";
    }
    else
        text="L'image n'a pas ete sauvegardee";

    error->setText(text);
    error->show();
}
