cmake_minimum_required(VERSION 3.17)
project(LabJob2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LabJob2
        ActionWindow.h
        CMainWindow.cpp
        CMainWindow.h
        CObject.cpp
        CObject.h
        Event.h
        main.cpp
        Window.cpp
        Window.h)
