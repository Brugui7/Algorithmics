cmake_minimum_required(VERSION 3.14)
project(Algorithmics C)

set(CMAKE_C_STANDARD 11)

include_directories(boletin1/model)

add_executable(Algorithmics
    boletin1/function/Film.c
    boletin1/model/Film.h
    boletin1/function/HashTable.c
    boletin1/model/HashTable.h
    boletin1/main.c)
