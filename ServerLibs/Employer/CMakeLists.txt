cmake_minimum_required(VERSION 3.22)

project(Employer_lib)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set(${CMAKE_CXX_FLAGS} "${CMAKE_CXX_FLAGS} -std=c++ly -Wall") 

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME} SHARED
                 	src/main.cpp
                 )
