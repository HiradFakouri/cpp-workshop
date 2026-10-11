#!/usr/bin/env bash
# This section builds real ROS2 packages with colcon, not plain CMake. Every
# exercise is its own package under src/exercises/ (or src/solutions/ for the
# --solution flag), sharing one colcon workspace rooted at this folder
# (build/, install/, log/ as siblings of src/ -- the standard colcon layout).
#
# Usage:
#   ./build.bash --exercise <1-4> [--solution] [--clean]
#
# Examples:
#   ./build.bash --exercise 1             # build + run exercises/ex1_publisher_and_timer
#   ./build.bash --exercise 1 --solution  # build + run solutions/ex1_publisher_and_timer_solution
#   ./build.bash --exercise 4 --clean     # wipe build/install/log first, then build + run exercise 4

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

EXERCISES=(
  "ex1_publisher_and_timer"
  "ex2_subscriber_and_callback"
  "ex3_ros_params"
  "ex4_wiring_header_files"
)

usage() {
  cat <<EOF
Usage: $(basename "$0") --exercise <1-4> [--solution] [--clean]

  --exercise <1-4>   which ros2 exercise to build and run (required)
  --solution         build the solutions/<name>_solution package instead
  --clean            wipe build/, install/, and log/ first, then reconfigure
  -h, --help         show this help

Exercises:
EOF
  for i in "${!EXERCISES[@]}"; do
    echo "  $((i + 1))  ${EXERCISES[$i]}"
  done
}

exercise_num=""
solution=false
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
  echo "error: --exercise <1-4> is required" >&2
  usage
  exit 1
fi

if ! [[ "${exercise_num}" =~ ^[1-4]$ ]]; then
  echo "error: --exercise must be a number from 1 to 4, got '${exercise_num}'" >&2
  exit 1
fi

name="${EXERCISES[$((exercise_num - 1))]}"
pkg="${name}"
if [[ "${solution}" == true ]]; then
  pkg="${name}_solution"
fi

if [[ ! -f /opt/ros/humble/setup.bash ]]; then
  echo "error: /opt/ros/humble/setup.bash not found -- is ROS2 Humble installed?" >&2
  exit 1
fi
# ROS2's own setup scripts aren't written to be safe under `set -u`, so it's
# relaxed just around sourcing them.
set +u
# shellcheck disable=SC1091
source /opt/ros/humble/setup.bash
set -u

if [[ "${clean}" == true ]]; then
  echo "Wiping build/, install/, log/..."
  rm -rf "${SCRIPT_DIR}/build" "${SCRIPT_DIR}/install" "${SCRIPT_DIR}/log"
fi

echo "Building ${pkg}..."
if ! (cd "${SCRIPT_DIR}" && colcon build --packages-select "${pkg}"); then
  echo ""
  echo "${pkg} failed to build. If this is an untouched exercise, that's" \
       "expected -- fix the compiler/linker errors above and run this again."
  exit 1
fi

set +u
# shellcheck disable=SC1090
source "${SCRIPT_DIR}/install/setup.bash"
set -u

echo ""
echo "Running ${pkg}..."
echo "----------------------------------------"
"${SCRIPT_DIR}/install/${pkg}/lib/${pkg}/${pkg}"
