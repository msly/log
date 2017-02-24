cmake_minimum_required(VERSION 2.8)
project(log)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opt/spdlog/include)

add_library(${PROJECT_NAME} STATIC Log.cpp Log.h)

set(LOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")