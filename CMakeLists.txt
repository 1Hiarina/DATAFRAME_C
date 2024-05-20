cmake_minimum_required(VERSION 3.26)
project(Projet_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_C main.c
        column.h
        column.c
        list.c
        list.h
        cdataframe.c
        cdataframe.h
)
