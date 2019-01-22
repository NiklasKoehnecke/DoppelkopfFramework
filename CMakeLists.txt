cmake_policy(SET CMP0048 NEW)
project(doppelkopf)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

set(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory(src)

set(EXE_NAME doppelkopf)

add_executable(${EXE_NAME} ${SOURCE} ${CORE})

#find_package(PythonLibs REQUIRED)
#target_include_directories(${EXE_NAME} PUBLIC ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(${EXE_NAME} PUBLIC ${PYTHON_LIBRARIES})

message("PYTHONLIBS")
message("   PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS}")
message("   PYTHON_LIBRARIES ${PYTHON_LIBRARIES}")

#tests are off by default, pass -DADD_TESTS=ON in to cmake to activate tests (and reset cache)
option(ADD_TESTS "Set to ON to build with tests." OFF)


IF(ADD_TESTS)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(libs/googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${COMMON_INCLUDES})


    add_subdirectory(tests)
if(COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif(COVERAGE)
    add_executable(tests_executable ${test_sources})
    target_link_libraries(tests_executable gtest_main)

    add_test(tests tests_executable)
ENDIF(ADD_TESTS)
