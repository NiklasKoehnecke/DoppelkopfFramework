cmake_policy(SET CMP0048 NEW)
project(doppelkopf)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

set(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory(src)
add_executable(doppelkopf ${SOURCE} ${CORE})

#tests are off by default, pass -DADD_TESTS=ON in to cmake to activate tests (and reset cache)
option(ADD_TESTS "Set to ON to build with tests." OFF)

IF(ADD_TESTS)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(libs/googletest)
    set(TEST_TARGET tests_executable)

    enable_testing()
    add_subdirectory(tests)

    add_executable(${TEST_TARGET} ${test_sources})

    target_include_directories(${TEST_TARGET} PUBLIC ${gtest_SOURCE_DIR}/include ${COMMON_INCLUDES})
    target_include_directories(${TEST_TARGET} PUBLIC src)


if(COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(COVERAGE)

    target_link_libraries(${TEST_TARGET} gtest_main)

    add_test(tests ${TEST_TARGET})
ENDIF(ADD_TESTS)
