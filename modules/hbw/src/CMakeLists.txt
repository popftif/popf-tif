project(hbw)

set( CMAKE_MODULE_PATH    ${CMAKE_MODULE_PATH}
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/cmake
                          )


find_package(Armadillo)

include_directories(${ARMADILLO_INCLUDES})

add_library(hbw SHARED HBWSolver.cpp ExternalSolver.cpp main.cpp)
add_executable(hbwMain HBWSolver.cpp ExternalSolver.cpp main.cpp)

target_link_libraries(hbw ${ARMADILLO_LIBRARIES})
target_link_libraries(hbwMain ${ARMADILLO_LIBRARIES})

#install(TARGETS hbw RUNTIME DESTINATION bin)
