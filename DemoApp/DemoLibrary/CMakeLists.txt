cmake_minimum_required(VERSION 3.29)
project(DemoLibrary)

set(CMAKE_CXX_STANDARD 20)

# Crear la librería como estática o compartida
add_library(DemoLibrary STATIC
        MPointerGC.cpp
        MemoryList.cpp
)

# Incluir los directorios de encabezados para que estén disponibles en proyectos que usen la librería
target_include_directories(DemoLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

