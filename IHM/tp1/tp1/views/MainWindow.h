#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QWidget>
#include "GraphicsImageScene.h"
#include "GraphicsImageView.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void addParameterWidget(QWidget *widget);
    GraphicsImageScene * getSceneDown();
    GraphicsImageScene * getSceneUp();
    
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
};
