cmake_minimum_required(VERSION 3.15)
project(DHBW_Buecherladen C)

set(CMAKE_C_STANDARD 11)

add_executable(DHBW_Buecherladen main.c zeug.h zeug.c dateien.c verketteteListe.c verketteteListe.h dateien.h main.h sort.c sort.h)