# Exercises build by default. None of them compile/link clean until you've filled
# in their TODOs -- that's expected, same as section 1.
add_executable(01_single_file_class exercises/01_single_file_class.cpp)

add_executable(02_header_source_split
  exercises/02_header_source_split/ConeLog.cpp
  exercises/02_header_source_split/main.cpp
)

add_executable(03_wiring_header_files
  exercises/03_wiring_header_files/Odometer.cpp
  exercises/03_wiring_header_files/main.cpp
)

# Note: 04_project_layout is deliberately NOT here -- see its own README section
# and exercises/04_project_layout/CMakeLists.txt for why.

# ConeMapAllInOne.cpp deliberately isn't listed here -- it's reference material to
# copy from, not part of the build. See the README and that file's own comment.
add_executable(05_class_across_multiple_files
  exercises/05_class_across_multiple_files/src/Recording.cpp
  exercises/05_class_across_multiple_files/src/Geometry.cpp
  exercises/05_class_across_multiple_files/src/Colours.cpp
  exercises/05_class_across_multiple_files/src/main.cpp
)
target_include_directories(05_class_across_multiple_files PRIVATE
  exercises/05_class_across_multiple_files/include
)

# Reference solutions only build if you ask for them: cmake -DBUILD_SOLUTIONS=ON ..
option(BUILD_SOLUTIONS "Also build the reference solutions" OFF)
if(BUILD_SOLUTIONS)
  add_executable(01_single_file_class_solution solutions/01_single_file_class.cpp)

  add_executable(02_header_source_split_solution
    solutions/02_header_source_split/ConeLog.cpp
    solutions/02_header_source_split/main.cpp
  )

  add_executable(03_wiring_header_files_solution
    solutions/03_wiring_header_files/Odometer.cpp
    solutions/03_wiring_header_files/main.cpp
  )

  add_executable(05_class_across_multiple_files_solution
    solutions/05_class_across_multiple_files/src/Recording.cpp
    solutions/05_class_across_multiple_files/src/Geometry.cpp
    solutions/05_class_across_multiple_files/src/Colours.cpp
    solutions/05_class_across_multiple_files/src/main.cpp
  )
  target_include_directories(05_class_across_multiple_files_solution PRIVATE
    solutions/05_class_across_multiple_files/include
  )
endif()
