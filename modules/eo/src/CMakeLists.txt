cmake_minimum_required(VERSION 3.2)
project(SaT)


set( CMAKE_MODULE_PATH    ${CMAKE_MODULE_PATH}
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/cmake
                          )


set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 ${CMAKE_CXX_FLAGS}")



add_library(SaT SHARED EasySolver.cpp ExternalSolver.cpp)
add_library(Dynamic SHARED DynamicSolver.cpp ExternalSolver.cpp)

