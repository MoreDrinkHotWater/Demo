cmake_minimum_required(VERSION 3.14)
project(demo_two)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core CONFIG)

aux_source_directory(. Common_SRCS)

list(APPEND Common_SRCS
        ./include/Color.h
        ./include/DataStructure.h
        ./include/VectorMapSingleton.h
        ./include/VMapToCSVSingleton.h
        ./include/VMapToJsonSingleton.h

        ./src/VectorMapSingleton.cpp
        ./src/VMapToCSVSingleton.cpp
        ./src/VMapToJsonSingleton.cpp
        )

add_library(Common SHARED ${Common_SRCS})
target_link_libraries(Common Qt5::Widgets Qt5::Core)