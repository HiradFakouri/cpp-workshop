# Exercise 3 has no code -- it's exercises/03_finding_things/QUESTIONS.md,
# answered against the real ugrdv workspace, not built.

find_package(Eigen3 REQUIRED)

add_executable(01_real_structures exercises/01_real_structures.cpp)
target_link_libraries(01_real_structures Eigen3::Eigen)

add_executable(02_eigen_basics exercises/02_eigen_basics.cpp)
target_link_libraries(02_eigen_basics Eigen3::Eigen)

option(BUILD_SOLUTIONS "Also build the reference solutions" OFF)
if(BUILD_SOLUTIONS)
  add_executable(01_real_structures_solution solutions/01_real_structures.cpp)
  target_link_libraries(01_real_structures_solution Eigen3::Eigen)

  add_executable(02_eigen_basics_solution solutions/02_eigen_basics.cpp)
  target_link_libraries(02_eigen_basics_solution Eigen3::Eigen)
endif()
