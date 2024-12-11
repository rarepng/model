cmake_minimum_required(VERSION 3.22)
project(model LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64")
list(APPEND CMAKE_PROGRAM_PATH  "C:/Qt/6.8.0/msvc2022_64/bin")


find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Gui)
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
