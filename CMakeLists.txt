project(doppelkopf)
cmake_minimum_required(VERSION 3.12)


#add_subdirectory(libs/googletest)
add_subdirectory(src)

add_executable(doppelkopf ${SOURCE} ${CORE})
#target_link_libraries(doppelkopf gtest_main)
#add_test(NAME example_test COMMAND example)