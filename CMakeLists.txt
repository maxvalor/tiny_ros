cmake_minimum_required(VERSION 3.0)

project(tiny_ros VERSION 1.0)

add_definitions(-std=c++11)

include_directories(
  include/mini_ros
)

include(cmake/sample.cmake)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
)
