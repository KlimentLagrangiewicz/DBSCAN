cmake_minimum_required(VERSION 3.20)

project(DBSCAN LANGUAGES C)

set(CMAKE_C_STANDARD 90)

add_executable(DBSCAN src/main.c src/help.h src/help.c src/dbscan.h src/dbscan.c)

target_link_libraries(DBSCAN m)

install(TARGETS DBSCAN
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
