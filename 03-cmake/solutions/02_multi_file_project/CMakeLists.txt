cmake_minimum_required(VERSION 3.16)
project(02_multi_file_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(02_multi_file_project
  src/TrackLog.cpp
  src/main.cpp
)
target_include_directories(02_multi_file_project PRIVATE include)
