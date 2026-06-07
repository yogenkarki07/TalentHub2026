cmake_minimum_required(VERSION 4.1)
project(TalentHub2026)

set(CMAKE_CXX_STANDARD 20)

add_executable(TalentHub2026 main.cpp
        course.cpp
        Headers/course.h
        Headers/menusManager.h
        Headers/Globals.h
)
