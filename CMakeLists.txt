cmake_minimum_required(VERSION 3.16)
project(cpp_workshop CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra)

add_subdirectory(01-foundations)
add_subdirectory(02-classes)
add_subdirectory(04-pointers)
add_subdirectory(06-our-code)
add_subdirectory(07-debugging)
