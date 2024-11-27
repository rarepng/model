cmake_minimum_required(VERSION 3.22)
project(model LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Svg
)


qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    model.ui
    model.hpp
    model.cpp
)

add_executable(model ${PROJECT_SOURCES})



target_link_libraries(model
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
)
