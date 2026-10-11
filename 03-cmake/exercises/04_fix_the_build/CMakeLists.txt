cmake_minimum_required(VERSION 3.16)
project(04_fix_the_build CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BUG 1: cone_report is built as a library, but nothing tells it where its own
# header lives. Building this target fails with "cone_report/ConeReport.hpp: No
# such file or directory" -- from inside ConeReport.cpp, which #includes its own
# header and can't find it.
add_library(cone_report src/ConeReport.cpp)

# BUG 2: 04_fix_the_build never links against cone_report. Once BUG 1 is fixed,
# building THIS target fails with the exact same "file not found" error as
# above, just for main.cpp instead -- because an executable that doesn't link
# against a library doesn't inherit that library's include directories either.
# Fixing this one bug resolves both symptoms: it's what actually connects the
# two targets, include path and all.
add_executable(04_fix_the_build src/main.cpp)
