cmake_minimum_required(VERSION 2.8)

project(CXX_Practice)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories(
    ${INCLUDE_DIR}
)

add_subdirectory(src)

add_executable(cxx_practice main.cpp $<TARGET_OBJECTS:samples>)
