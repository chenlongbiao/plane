cmake_minimum_required(VERSION 3.14)
project(plane C)

set(CMAKE_C_STANDARD 11)

add_executable(plane main.c ansi.h util.c util.h model.h)