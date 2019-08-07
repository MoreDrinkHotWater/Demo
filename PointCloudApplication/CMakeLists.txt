cmake_minimum_required(VERSION 3.14)
project(demo_two)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core CONFIG)

find_package(Qt5Xml)

find_package(PCL REQUIRED)

set(RESOURCE_DIR ../ui/icon.qrc)

set(POINTCLOUDAPPLICATION_INCLUDE ./include)
set(MAINWINDOW_H ${POINTCLOUDAPPLICATION_INCLUDE}/mainWindow.h)
set(GENERATEOCTREEWORKER_H ${POINTCLOUDAPPLICATION_INCLUDE}/GenerateOctreeWorker.h)
set(OPENFILEDIALOG_H ${POINTCLOUDAPPLICATION_INCLUDE}/OpenFileDialog.h)



set(POINTCLOUDAPPLICATION_SRCS ./src)
set(MAINWINDOW_CPP ${POINTCLOUDAPPLICATION_SRCS}/mainWindow.cpp)
set(GENERATEOCTREEWORKER_CPP ${POINTCLOUDAPPLICATION_SRCS}/GenerateOctreeWorker.cpp)
set(OPENFILEDIALOG_CPP ${POINTCLOUDAPPLICATION_SRCS}/OpenFileDialog.cpp include/NewFileDialog.h src/NewFileDialog.cpp include/AddConsoleDialog.h src/AddConsoleDialog.cpp include/Toolbar.h src/Toolbar.cpp)

aux_source_directory(. PointCloudApplication_SRCS)

list(APPEND PointCloudApplication_SRCS
        ./include/NewFileDialog.h
        include/AddConsoleDialog.h

        ./src/NewFileDialog.cpp
        src/AddConsoleDialog.cpp)

add_executable(PointCloudApplication  ${RESOURCE_DIR} ${PCL_INCLUDE_DIRS} ${PointCloudApplication_SRCS} ${MAINWINDOW_H} ${MAINWINDOW_CPP}   ${GENERATEOCTREEWORKER_H} ${GENERATEOCTREEWORKER_CPP} ${OPENFILEDIALOG_H} ${OPENFILEDIALOG_CPP})

target_include_directories(PointCloudApplication PRIVATE  ../common ../OSGWidgets)
target_link_libraries(PointCloudApplication Qt5::Widgets Qt5::Xml OSGWidgets Common ${PCL_LIBRARIES})
