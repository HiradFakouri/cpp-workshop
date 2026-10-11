# Exercises build by default. None of them compile clean until you've filled in
# their TODOs -- that's expected, same as sections 1 and 2.
add_executable(01_pointers_and_references_basics exercises/01_pointers_and_references_basics.cpp)
add_executable(02_star_vs_amp exercises/02_star_vs_amp.cpp)
add_executable(03_swap exercises/03_swap.cpp)
add_executable(04_rewrite_with_pointers exercises/04_rewrite_with_pointers.cpp)

# Reference solutions only build if you ask for them: cmake -DBUILD_SOLUTIONS=ON ..
option(BUILD_SOLUTIONS "Also build the reference solutions" OFF)
if(BUILD_SOLUTIONS)
  add_executable(01_pointers_and_references_basics_solution solutions/01_pointers_and_references_basics.cpp)
  add_executable(02_star_vs_amp_solution solutions/02_star_vs_amp.cpp)
  add_executable(03_swap_solution solutions/03_swap.cpp)
  add_executable(04_rewrite_with_pointers_solution solutions/04_rewrite_with_pointers.cpp)
endif()
