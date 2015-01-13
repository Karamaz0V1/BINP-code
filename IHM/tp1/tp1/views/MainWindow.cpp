#include "views/MainWindow.h"
#include "AbstractParametersWidget.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
{
    m_menuBar=new QMenuBar(this);
    m_fileMenu = new QMenu("File",m_menuBar);
    m_openAction = m_fileMenu->addAction("&Open");
    m_saveAction = m_fileMenu->addAction("&Save");
    m_quitAction = m_fileMenu->addAction("&Quit");
    m_tabWidget=new QTabWidget(this);
    m_graphicsSceneUp=new GraphicsImageScene(this);
    m_graphicsSceneDown=new GraphicsImageScene(this);
    m_graphicsViewUp=new GraphicsImageView(m_graphicsSceneUp);
    m_graphicsViewDown=new GraphicsImageView(m_graphicsSceneDown);
    m_layout=new QHBoxLayout();
    m_layout->addWidget(m_tabWidget);
    m_layout2=new QVBoxLayout();
    m_layout2->addWidget(m_graphicsViewUp);
    m_layout2->addWidget(m_graphicsViewDown);
    m_layout->addLayout(m_layout2);
    m_menuBar->addMenu(m_fileMenu);
    this->setMenuBar(m_menuBar);
    m_central=new QWidget(this);
    m_central->setLayout(m_layout);
    this->setCentralWidget(m_central);

    QObject::connect(m_openAction,SIGNAL(triggered()),m_graphicsSceneUp,SLOT(printImage()));
    QObject::connect(m_saveAction,SIGNAL(triggered()),m_graphicsSceneDown,SLOT(saveImage()));
    QObject::connect(m_quitAction,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::setInteractive(bool intercative) {
    m_graphicsSceneUp->setInteractive(intercative);
}

GraphicsImageScene * MainWindow::getSceneDown() {
    return m_graphicsSceneDown;
}

GraphicsImageScene * MainWindow::getSceneUp() {
    return m_graphicsSceneUp;
}

void MainWindow::addParameterWidget(AbstractParametersWidget *widget) {
    m_tabWidget->addTab(widget,widget->title());
}
