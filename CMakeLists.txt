cmake_minimum_required(VERSION 3.16)
project(filecrypt LANGUAGES CXX)

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

find_package(OpenSSL REQUIRED)

qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    filecrypt.ui
    filecrypt.hpp
    filecrypt.cpp
)

add_executable(filecrypt ${PROJECT_SOURCES})


set_target_properties(filecrypt
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(filecrypt
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        OpenSSL::Crypto
)

target_include_directories(filecrypt
    PUBLIC
    ### add includes for windows
)
