cmake_policy(SET CMP0048 NEW)
project(doppelkopf)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

set(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory(src)



add_executable(doppelkopf ${SOURCE} ${CORE})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(doppelkopf ${PYTHON_LIBRARIES})

#tests are off by default, pass -DADD_TESTS=ON in to cmake to activate tests (and reset cache)
option(ADD_TESTS "Set to ON to build with tests." OFF)

IF(ADD_TESTS)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(libs/googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${COMMON_INCLUDES})
    include_directories(src)


    add_subdirectory(tests)
if(COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(COVERAGE)
    add_executable(tests_executable ${test_sources})
    target_link_libraries(tests_executable gtest_main)

    add_test(tests tests_executable)
ENDIF(ADD_TESTS)
