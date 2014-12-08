#include "graphicsimagescene.h"

GraphicsImageScene::GraphicsImageScene(QWidget *window, QObject *parent) :
    QGraphicsScene(parent)
{
    m_window=window;
}

GraphicsImageScene::~GraphicsImageScene() {

}

void GraphicsImageScene::setImage(const QImage &image) {
    m_image=image;
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem();
    QPixmap pixmap = QPixmap::fromImage(m_image);
    pixmapItem->setPixmap(pixmap);
    this->addItem(pixmapItem);
}

QImage GraphicsImageScene::image() const {
    return m_image;
}

void GraphicsImageScene::printImage() {
    QWidget *window = m_window;
    QString title = "Ouvrir";
    QString dir = "~";
    QString filters = tr("Images (*.png *.xpm *.jpg *.bnp)");
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

void GraphicsImageScene::saveImage() {
    QWidget *window = m_window;
    QString title = "Enregistrer";
    QString dir = "~";
    QString filters = tr("Images (*.png *.xpm *.jpg *.bnp)");
    QFileDialog *file = new QFileDialog(window,title,dir,filters);
    QStringList chosenFile;
    file->setFileMode(QFileDialog::AnyFile);
    file->show();
    if(file->exec())
        chosenFile=file->selectedFiles();
    QString fileName=chosenFile.first();

    QMessageBox* error = new QMessageBox();
    QString text;
    if(!image().save(fileName))
        text="L'image n'a pas été sauvegardée";
    else
        text="L'image a bien été sauvegardée";
    error->setText(text);
    error->show();
}
