add_subdirectory(core)
add_subdirectory(exampleBot)
add_subdirectory(pythonBot)

#this has to be here to propegate all the sources to the highest cmakelist
set(SOURCE ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        PARENT_SCOPE)

set(CORE ${CORE} PARENT_SCOPE)