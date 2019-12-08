cmake_minimum_required(VERSION 3.14)
project(Algorithmics C)

set(CMAKE_C_STANDARD 11)

include_directories(boletin3/model)

add_executable(Algorithmics
    boletin3/main.c
        boletin3/function/BubbleSort.c boletin3/model/BubbleSort.h boletin3/model/Common.h boletin3/function/Common.c boletin3/function/SelectionSort.c boletin3/model/SelectionSort.h boletin3/function/ShellSort.c boletin3/model/ShellSort.h)
