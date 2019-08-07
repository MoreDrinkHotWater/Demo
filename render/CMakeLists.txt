cmake_minimum_required(VERSION 3.14)
project(OSGWidgets)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui OpenGL CONFIG)

find_package(OpenSceneGraph 3.2 REQUIRED COMPONENTS osgGA osgViewer osgDB osgUtil osg osgQt osgFX)
find_package(PCL REQUIRED)
# C++和C版本的都要安装，不然会报错找不到capi/version.h文件，其中库文件地址简写为libLAS_LIBRARIES，而不是LIBLAS_LIBRARIES
find_package(libLAS REQUIRED)
find_package(Eigen3 REQUIRED)

aux_source_directory(. OSGWidget_SRCS)

list(APPEND OSGWidget_SRCS
        ./include/OSGWidget.h
        ./include/ProgressBarWorker.h
        ./include/NodeNames.h
        ./include/NodeTreeHandler.h
        ./include/NodeTreeInfo.h
        ./include/NodeTreeSearch.h
        ./include/TextController.h
        ./include/LineEditor.h
        ./include/Measurement.h
        ./include/ShowCoordinateAxis.h
        ./include/NewFile.h

        ./src/OSGWidget.cpp
        ./src/ProgressBarWorker.cpp
        ./src/ENUCoorConv.hpp
        ./src/NodeTreeHandler.cpp
        ./src/NodeTreeInfo.cpp
        ./src/NodeTreeSearch.cpp
        ./src/TextController.cpp
        ./src/LineEditor.cpp
        ./src/Measurement.cpp
        ./src/ShowCoordinateAxis.cpp
        ./src/NewFile.cpp)

add_library(OSGWidgets SHARED ${OSGWidget_SRCS} include/NewFile.h src/NewFile.cpp include/ClearIrrelevantPoints.h src/ClearIrrelevantPoints.cpp include/ClearPointsEvents.h src/ClearPointsEvents.cpp)

target_include_directories(OSGWidgets PUBLIC ../common ${OPENSCENEGRAPH_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} ${LIBLAS_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

target_link_libraries(OSGWidgets Qt5::Widgets Common ${OPENSCENEGRAPH_LIBRARIES} ${PCL_LIBRARIES} ${libLAS_LIBRARIES})




