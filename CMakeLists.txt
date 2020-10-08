cmake_minimum_required(VERSION 3.13)
project(mova1701_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mova1701_Project
       
        company.cpp
        company.h
        event.cpp
        event.h
        filehandler.cpp
        filehandler.h
        helpfunctions.cpp
        helpfunctions.h
        locomotive.cpp
        locomotive.h
        main.cpp
        mempool.h
        memstat.hpp
        menu.cpp
        menu.h
        simulation.cpp
        simulation.h
        stationdistance.cpp
        stationdistance.h
        testapp.cpp
        testapp.h
        train.cpp
        train.h
        trainstation.cpp
        trainstation.h
        vehicle.cpp
        vehicle.h)
