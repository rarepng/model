cmake_minimum_required(VERSION 3.22)
project(model LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)





list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt-6.8.1")
list(APPEND CMAKE_PROGRAM_PATH  "C:/Qt/Qt-6.8.1/bin")


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





set(resources_bin_dir "${PROJECT_BINARY_DIR}/resources")
add_custom_command(
    OUTPUT ${resources_bin_dir}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources" "${PROJECT_BINARY_DIR}/resources"
    DEPENDS "${PROJECT_SOURCE_DIR}/resources"
)
add_custom_target(resources_bin_deps DEPENDS ${PROJECT_BINARY_DIR}/resources)
add_dependencies(model resources_bin_deps)









target_link_libraries(model
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
)

target_link_options(model PRIVATE -static)
#set_property(TARGET model PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
