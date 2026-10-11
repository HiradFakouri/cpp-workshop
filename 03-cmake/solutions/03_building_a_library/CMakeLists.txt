cmake_minimum_required(VERSION 3.16)
project(03_building_a_library CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cone_math src/ConeMath.cpp)
target_include_directories(cone_math PUBLIC include)

add_executable(03_building_a_library src/main.cpp)
target_link_libraries(03_building_a_library PRIVATE cone_math)
