cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(buildroot)

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

set(CMAKE_CXX_FLAGS_PROFILE "-g3 -pg -O -fprofile-arcs")
set(CMAKE_CXX_LINK_FLAGS_PROFILE "-pg")

set(CMAKE_CXX_FLAGS_ALMOSTRELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_LINK_FLAGS_ALMOSTRELEASE "")

set(CMAKE_CXX_FLAGS_O3DEBUG "-O3 -g")
set(CMAKE_CXX_LINK_FLAGS_O3DEBUG "-g")


add_subdirectory(VALfiles)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lprpg")
	add_subdirectory(lprpg)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lprpg")


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/popf")
	add_subdirectory(popf)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/popf")


