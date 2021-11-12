cmake_minimum_required(VERSION 3.20)
project(Datos-ll-Proyecto-2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp cargarImagen.cpp cargarImagen.h algoritmoGenetico.cpp algoritmoGenetico.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(Datos-ll-Proyecto-2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )