cmake_minimum_required(VERSION 3.23)
project(SoftwareProjectFinal C)

set(CMAKE_C_STANDARD 90)

add_executable(SoftwareProjectFinal spkmeans.c
        spkmeans.h
        wam.c
        ddg.c
        Makefile)
