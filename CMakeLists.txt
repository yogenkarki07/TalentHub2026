cmake_minimum_required(VERSION 3.20)
project(TalentHub2026)

set(CMAKE_CXX_STANDARD 20)

add_executable(TalentHub2026
        main.cpp
        student.cpp
        Headers/student.h
        validation.cpp
        Headers/validation.h
        filehandler.cpp
        Headers/filehandler.h
        course.cpp
        Headers/course.h
        Headers/Globals.h
        Headers/menu.h
        menu.cpp
)