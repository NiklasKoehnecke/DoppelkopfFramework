project(doppelkopf)
cmake_minimum_required(VERSION 3.12)

add_subdirectory(src)

add_executable(doppelkopf ${SOURCE} ${CORE})