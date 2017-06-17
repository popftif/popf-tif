project(SaT)


set( CMAKE_MODULE_PATH    ${CMAKE_MODULE_PATH}
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/cmake
                          )


set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 ${CMAKE_CXX_FLAGS}")



add_library(SaT SHARED SaTSolver.cpp ExternalSolver.cpp)
add_executable(SaTMain SaTSolver.cpp ExternalSolver.cpp main.cpp)

