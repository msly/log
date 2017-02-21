cmake_minimum_required(VERSION 2.8)
project(log)

include_directories(.)

add_library(log SHARED Log.cpp Log.h)

set(LOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")