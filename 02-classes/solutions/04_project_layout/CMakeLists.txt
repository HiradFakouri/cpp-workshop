cmake_minimum_required(VERSION 3.16)
project(cone_counter_layout_exercise CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(04_project_layout
  src/ConeCounter.cpp
  src/main.cpp
)
target_include_directories(04_project_layout PRIVATE include)
