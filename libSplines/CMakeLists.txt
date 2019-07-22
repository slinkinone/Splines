cmake_minimum_required(VERSION 2.6.0)
project(Spline C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(LIBRARY_NAME "${PROJECT_NAME}")
option(BUILD_SHARED_LIBS "Build ${LIBRARY_NAME} as a shared library." OFF)

if(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE SHARED)
else()
  set(LIBRARY_TYPE STATIC)
endif()

file(GLOB INCLUDE_DIR
        include
)

file(GLOB SOURCE_DIR
    src/*.c
)

include_directories (${INCLUDE_DIR})

add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_link_libraries(${PROJECT_NAME} m)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
    ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)