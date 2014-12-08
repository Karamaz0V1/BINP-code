#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>
#include <QHBoxLayout>
#include "graphicsimagescene.h"
#include "graphicsimageview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_quitAction;
    QTabWidget* m_tabWidget;
    QGraphicsView* m_graphicsViewUp;
    QGraphicsView* m_graphicsViewDown;
    GraphicsImageScene* m_graphicsSceneUp;
    GraphicsImageScene* m_graphicsSceneDown;
    QHBoxLayout* m_layout;
    QVBoxLayout* m_layout2;
    QWidget* m_central;
    //QLabel m_label;
    //Q
    //QPushButton m_button;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
