cmake_minimum_required(VERSION 3.21)
project(Proyecto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto
        arbolTorneo.h
        cargarEquipos.h
        clasificatorias.h
        main.cpp)
