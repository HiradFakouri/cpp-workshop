# Debug symbols matter more than usual in this section -- the root
# CMakeLists.txt already defaults CMAKE_BUILD_TYPE to Debug, but -g is added
# explicitly here too so gdb always has line info regardless of how this
# subdirectory ends up built.
add_compile_options(-g)

add_executable(01_segfault_and_gdb exercises/01_segfault_and_gdb.cpp)
add_executable(02_stepping_through_a_bug exercises/02_stepping_through_a_bug.cpp)

option(BUILD_SOLUTIONS "Also build the reference solutions" OFF)
if(BUILD_SOLUTIONS)
  add_executable(01_segfault_and_gdb_solution solutions/01_segfault_and_gdb.cpp)
  add_executable(02_stepping_through_a_bug_solution solutions/02_stepping_through_a_bug.cpp)
endif()
