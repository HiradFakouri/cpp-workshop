cmake_minimum_required(VERSION 3.8)
project(ex4_wiring_header_files)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# This CMakeLists.txt has two bugs in it -- everything else in this package
# (the .hpp, the two .cpp files) is complete and correct. Fix this file, not
# the C++.

add_executable(ex4_wiring_header_files
  src/CounterNode.cpp
  src/main.cpp
)

# BUG 1: nothing tells this target where include/ is. Building fails with
# "ex4_wiring_header_files/CounterNode.hpp: No such file or directory" --
# from CounterNode.cpp, which is the first file that #includes it.
#
# BUG 2: once BUG 1 is fixed, building fails again with the exact same "No
# such file or directory" error, just for rclcpp/rclcpp.hpp instead -- from
# inside CounterNode.hpp itself. find_package(rclcpp REQUIRED) above only
# finds rclcpp on this machine; it doesn't hand its headers (or its compiled
# library) to any particular target. That's ament_target_dependencies()'s
# job, and it's missing here.
install(TARGETS ex4_wiring_header_files DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
