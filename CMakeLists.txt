cmake_minimum_required(VERSION 3.0)
project(SimpleMovingAverage)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SimpleMovingAverage main.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)