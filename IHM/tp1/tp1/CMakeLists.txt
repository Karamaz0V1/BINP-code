cmake_minimum_required(VERSION 2.8)

project(ihm)

# Qt
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(CMAKE_AUTOMOC ON)

# ViSP
find_package(VISP REQUIRED)
include(${VISP_USE_FILE})

# Find includes in corresponding build directories
include_directories(
    views
    presenters
    models
    )
set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(${PROJECT_NAME}_CPP
    main.cpp
    views/MainWindow.cpp
    views/GraphicsImageScene.cpp
    views/GraphicsImageView.cpp
    views/ResizeImageParametersWidget.cpp
    views/AbstractParametersWidget.cpp
    models/ResizeModel.cpp
    models/AbstractModel.cpp
    presenters/AbstractPresenter.cpp
    presenters/ResizePresenter.cpp
    )

set(${PROJECT_NAME}_H
    ImageConverter.h
    views/MainWindow.h
    views/GraphicsImageScene.h
    views/GraphicsImageView.h
    views/ResizeImageParametersWidget.h
    models/ResizeModel.h
    models/AbstractModel.h
    views/AbstractParametersWidget.h
    presenters/AbstractPresenter.h
    presenters/ResizePresenter.h
    )

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_CPP}
    ${${PROJECT_NAME}_H}
    )

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES}
    )
