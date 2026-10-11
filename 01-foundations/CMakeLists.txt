# Exercises build by default. None of them compile clean until you've filled in
# their TODOs (03 is deliberately full of compiler errors) -- that's expected.
add_executable(01_loops_and_data_types exercises/01_loops_and_data_types.cpp)
add_executable(02_custom_data_structures exercises/02_custom_data_structures.cpp)
add_executable(03_reading_compiler_errors exercises/03_reading_compiler_errors.cpp)
add_executable(04_const_correctness exercises/04_const_correctness.cpp)

# Reference solutions only build if you ask for them: cmake -DBUILD_SOLUTIONS=ON ..
# Have a real go at each exercise before turning this on.
option(BUILD_SOLUTIONS "Also build the reference solutions" OFF)
if(BUILD_SOLUTIONS)
  add_executable(01_loops_and_data_types_solution solutions/01_loops_and_data_types.cpp)
  add_executable(02_custom_data_structures_solution solutions/02_custom_data_structures.cpp)
  add_executable(03_reading_compiler_errors_solution solutions/03_reading_compiler_errors.cpp)
  add_executable(04_const_correctness_solution solutions/04_const_correctness.cpp)
endif()
