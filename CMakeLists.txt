project(doppelkopf)
cmake_minimum_required(VERSION 3.12)

set(gtest_force_shared_crt ON)

add_subdirectory(src)
add_executable(doppelkopf ${SOURCE} ${CORE})

#tests are off by default, pass -DADD_TESTS=ON in to cmake to activate tests (and reset cache)
option(ADD_TESTS "Set to ON to build with tests." OFF)

IF(ADD_TESTS)

    add_subdirectory(libs/googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${COMMON_INCLUDES})

    add_subdirectory(tests)
    add_executable(tests_executable ${test_sources})
    target_link_libraries(tests_executable gtest_main)

    add_test(NAME TestAll COMMAND tests_executable)
ENDIF(ADD_TESTS)
