# This CMakeLists.txt is already correct and won't need editing -- but it's not
# part of the shared workshop build. It expects to find:
#
#   include/cone_counter/ConeCounter.hpp
#   src/ConeCounter.cpp
#   src/main.cpp
#
# ...none of which exist yet. Your job isn't to write C++ here -- ConeCounter is
# already finished and correct -- it's to physically move the three files that
# currently sit flat in this folder into that layout, and fix the one #include
# line in each .cpp that points at the header, so this actually configures and
# builds. See this section's README for the full task description.

cmake_minimum_required(VERSION 3.16)
project(cone_counter_layout_exercise CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(04_project_layout
  src/ConeCounter.cpp
  src/main.cpp
)
target_include_directories(04_project_layout PRIVATE include)
