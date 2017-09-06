include_directories(${val_SOURCE_DIR} ${val_SOURCE_DIR}/parsing ${val_BINARY_DIR} )

add_executable(insttest pat/insttest.cpp)

target_link_libraries(insttest
    ParsePDDL
    Inst
)

set(insttest_PATH ${CMAKE_CURRENT_BINARY_DIR}/insttest)
set(checkplanstepsexist_PATH ${CMAKE_CURRENT_SOURCE_DIR}/checkplanstepsexist)

add_subdirectory(pat)
add_subdirectory(tpp1)
add_subdirectory(storage3)
add_subdirectory(storage1)
add_subdirectory(satellite-til-1)
add_subdirectory(pipes-strips-1)
add_subdirectory(cafe-1)
add_subdirectory(airport20)
add_subdirectory(spanner)
add_subdirectory(landing)
add_subdirectory(logisticsinst)

