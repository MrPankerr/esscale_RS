cmake_minimum_required(VERSION 3.22)

project(ServerS)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set(${CMAKE_CXX_FLAGS} "${CMAKE_CXX_FLAGS} -std=c++ly -Wall")   

configure_file(
                "${PROJECT_SOURCE_DIR}/include/ver.h.in"
                "${PROJECT_BINARY_DIR}/version.h"
                )

configure_file(
                "${PROJECT_SOURCE_DIR}/include/path.h.in"
                "${PROJECT_BINARY_DIR}/path.h"
                )

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB
        CPPS "src/*.cpp")

link_directories(${CMAKE_SOURCE_DIR}/libs/shared)

add_executable(${PROJECT_NAME} ${CPPS})

target_link_libraries(${PROJECT_NAME}
                        Employer_lib.dll
                        Worker_lib.dll
)