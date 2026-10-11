#!/usr/bin/env bash
# Exercises 1-2 share the workshop-wide build/ dir (sections 1, 2, 4, 6).
# Exercise 3 is a real ROS2 package, built with colcon (section 5's toolchain)
# -- same reason as always: gdb doesn't care which build system produced the
# binary, and this section wants you to see that for yourself.
#
# This script only builds and (unless --no-run is passed) runs the binary --
# it deliberately does NOT invoke gdb for you. The whole point of this
# section is running gdb yourself: `gdb <path>`, then typing `run`, `bt`,
# `break`, `next`, `print` yourself. A wrapper script that did that step for
# you would be teaching you to run this script, not to use a debugger.
#
# Usage:
#   ./build.bash --exercise <1-3> [--solution] [--no-run] [--clean]
#
# Examples:
#   ./build.bash --exercise 1             # build + run exercises/01_segfault_and_gdb.cpp (crashes)
#   ./build.bash --exercise 1 --no-run    # just build, print the binary path, don't run it
#   ./build.bash --exercise 2 --solution  # build + run the fixed version
#
# Then, yourself, in your own terminal:
#   gdb <the path this script printed>

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"

EXERCISES=(
  "01_segfault_and_gdb"
  "02_stepping_through_a_bug"
  "ros2_node_crash"
)

usage() {
  cat <<EOF
Usage: $(basename "$0") --exercise <1-3> [--solution] [--no-run] [--clean]

  --exercise <1-3>   which debugging exercise to build (required)
  --solution         build the fixed version instead of the buggy one
  --no-run           just build and print the binary's path, don't run it
  --clean            wipe build state first, then reconfigure from scratch
  -h, --help         show this help

This never runs gdb for you -- once it prints the binary's path, run
'gdb <that path>' yourself.

Exercises:
  1  01_segfault_and_gdb        (plain CMake, shared build/)
  2  02_stepping_through_a_bug  (plain CMake, shared build/)
  3  ros2_node_crash            (real ROS2 package, colcon)
EOF
}

exercise_num=""
solution=false
no_run=false
clean=false

while [[ $# -gt 0 ]]; do
  case "$1" in
    --exercise)
      exercise_num="${2:-}"
      shift 2
      ;;
    --solution)
      solution=true
      shift
      ;;
    --no-run)
      no_run=true
      shift
      ;;
    --clean)
      clean=true
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [[ -z "${exercise_num}" ]]; then
  echo "error: --exercise <1-3> is required" >&2
  usage
  exit 1
fi

if ! [[ "${exercise_num}" =~ ^[1-3]$ ]]; then
  echo "error: --exercise must be a number from 1 to 3, got '${exercise_num}'" >&2
  exit 1
fi

name="${EXERCISES[$((exercise_num - 1))]}"

# --- Exercise 3: real ROS2 package, colcon ---------------------------------------
if [[ "${exercise_num}" == "3" ]]; then
  pkg="${name}"
  if [[ "${solution}" == true ]]; then
    pkg="${name}_solution"
  fi

  if [[ ! -f /opt/ros/humble/setup.bash ]]; then
    echo "error: /opt/ros/humble/setup.bash not found -- is ROS2 Humble installed?" >&2
    exit 1
  fi

  if [[ "${clean}" == true ]]; then
    echo "Wiping ${SCRIPT_DIR}/build, install, log..."
    rm -rf "${SCRIPT_DIR}/build" "${SCRIPT_DIR}/install" "${SCRIPT_DIR}/log"
  fi

  set +u
  # shellcheck disable=SC1091
  source /opt/ros/humble/setup.bash
  set -u

  echo "Building ${pkg}..."
  if ! (cd "${SCRIPT_DIR}" && colcon build --packages-select "${pkg}"); then
    echo ""
    echo "${pkg} failed to build. If this is unexpected, check the errors above." >&2
    exit 1
  fi

  bin="${SCRIPT_DIR}/install/${pkg}/lib/${pkg}/${pkg}"
  echo ""
  echo "Binary: ${bin}"
  echo "Debug it yourself with: gdb ${bin}"

  if [[ "${no_run}" == true ]]; then
    exit 0
  fi

  echo ""
  echo "Running ${pkg}..."
  echo "----------------------------------------"
  "${bin}"
  exit $?
fi

# --- Exercises 1-2: shared workshop build ----------------------------------------
target="${name}"
build_solutions_flag="OFF"
if [[ "${solution}" == true ]]; then
  target="${name}_solution"
  build_solutions_flag="ON"
fi

if [[ "${clean}" == true ]]; then
  echo "Wiping ${BUILD_DIR}..."
  rm -rf "${BUILD_DIR}"
fi

mkdir -p "${BUILD_DIR}"

echo "Configuring (BUILD_SOLUTIONS=${build_solutions_flag})..."
if ! cmake -S "${REPO_ROOT}" -B "${BUILD_DIR}" -DBUILD_SOLUTIONS="${build_solutions_flag}" >/dev/null; then
  echo "error: cmake configure failed" >&2
  exit 1
fi

echo "Building ${target}..."
if ! cmake --build "${BUILD_DIR}" --target "${target}"; then
  echo "error: build failed" >&2
  exit 1
fi

bin="${BUILD_DIR}/07-debugging/${target}"
echo ""
echo "Binary: ${bin}"
echo "Debug it yourself with: gdb ${bin}"

if [[ "${no_run}" == true ]]; then
  exit 0
fi

echo ""
echo "Running ${target}..."
echo "----------------------------------------"
"${bin}"
