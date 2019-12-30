cmake_minimum_required(VERSION 3.14)
project(Algorithmics C)

set(CMAKE_C_STANDARD 11)

include_directories(boletin4/model)

add_executable(Algorithmics
    boletin4/main.c
        boletin4/model/Common.h boletin4/function/Common.c
        boletin4/model/DirectSearch.h boletin4/function/DirectSearch.c
        )
