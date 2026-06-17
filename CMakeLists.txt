cmake_minimum_required(VERSION 3.20)
project(TalentHub2026)

set(CMAKE_CXX_STANDARD 20)

add_executable(TalentHub2026
        main.cpp
        menu.cpp
        Admin_menu.cpp
        student.cpp
        validation.cpp
        filehandler.cpp
        course.cpp
        Headers/course.h
        Headers/Globals.h
        Admin_menu.h
        Headers/Universal.h
)