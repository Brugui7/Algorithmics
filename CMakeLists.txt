cmake_minimum_required(VERSION 3.14)
project(Algorithmics C)

set(CMAKE_C_STANDARD 11)

include_directories(boletin2/model)

add_executable(Algorithmics
    boletin2/main.c
        boletin2/model/Exercise1.h
        boletin2/function/Exercise1.c
        )
