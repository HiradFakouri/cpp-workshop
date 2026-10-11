cmake_minimum_required(VERSION 3.16)
project(04_fix_the_build CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cone_report src/ConeReport.cpp)
target_include_directories(cone_report PUBLIC include)

add_executable(04_fix_the_build src/main.cpp)
target_link_libraries(04_fix_the_build PRIVATE cone_report)
