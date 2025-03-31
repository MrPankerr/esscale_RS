cmake_minimum_required(VERSION 3.22)

project(Client)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set(${CMAKE_CXX_FLAGS} "${CMAKE_CXX_FLAGS} -std=c++ly -Wall")   

add_executable(${PROJECT_NAME}W ./src/ClientW.cpp)
add_executable(${PROJECT_NAME}E ./src/ClientE.cpp)
