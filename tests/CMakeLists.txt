add_subdirectory(core)


set(test_sources ${test_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        PARENT_SCOPE)