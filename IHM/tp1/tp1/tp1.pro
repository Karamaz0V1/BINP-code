#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T08:19:57
#
#-------------------------------------------------

QT       += core gui

TARGET = tp1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsimagescene.cpp \
    graphicsimageview.cpp \
    models/ResizeModel.cpp \
    views/ResizeImageParametersWidget.cpp \
    views/MainWindow.cpp \
    views/GraphicsImageView.cpp \
    views/GraphicsImageScene.cpp \
    presenters/ResizePresenter.cpp \
    presenters/AbstractPresenter.cpp \
    models/AbstractModel.cpp \
    views/inpaintingparameterwidget.cpp \
    views/InpaintingParameterWidget.cpp \
    presenters/InpaintingPresenter.cpp

HEADERS  += mainwindow.h \
    graphicsimagescene.h \
    graphicsimageview.h \
    models/ResizeModel.h \
    views/ResizeImageParametersWidget.h \
    views/MainWindow.h \
    views/GraphicsImageView.h \
    views/GraphicsImageScene.h \
    models/AbstractModel.h \
    views/AbstractParametersWidget.h \
    presenters/ResizePresenter.h \
    presenters/AbstractPresenter.h \
    ImageConverter.h \
    views/InpaintingParameterWidget.h \
    presenters/InpaintingPresenter.h

FORMS    += mainwindow.ui
