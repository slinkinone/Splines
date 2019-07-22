cmake_minimum_required(VERSION 2.6.0)
project(spline)

option(DYNAMIC_LINK_TYPE "Build ${DYNAMIC_LINK_TYPE} as a shared library." OFF)

if(DYNAMIC_LINK_TYPE)
  set(LIBRARY_SUFFIX "so")
else()
  set(LIBRARY_SUFFIX "a")
endif()


set(SPLINE_LIB_PATH "${CMAKE_SOURCE_DIR}/libSplines/lib")
set(SPLINE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/libSplines/include")

find_library(
        SPLINE_LIB
        NAMES "Spline.${LIBRARY_SUFFIX}"
        HINTS "${SPLINE_LIB_PATH}"
)

if(NOT SPLINE_LIB)
  message(FATAL_ERROR "Spline library has not been found. [${SPLINE_LIB}]")
endif()

message(${SPLINE_INCLUDE_PATH})
message(${SPLINE_LIB_PATH})
message(${SPLINE_LIB})

include_directories(${SPLINE_INCLUDE_PATH})
#link_directories("${SPLINE_LIB_PATH}")

add_executable(${PROJECT_NAME} main.c)

if(NOT DYNAMIC_LINK_TYPE)
  target_link_libraries(${PROJECT_NAME} m)
endif()

target_link_libraries(${PROJECT_NAME} ${SPLINE_LIB})

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)