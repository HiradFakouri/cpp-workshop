#!/usr/bin/env bash
# Wrapper around the CMake build documented in the top-level README.
#
# Exercises 1-3 and 5 share the workshop-wide build/ dir at the repo root, same as
# section 1. Exercise 4 is different on purpose: it's a self-contained mini
# project with its own CMakeLists.txt (see exercises/04_project_layout/), and it
# starts in a state where that CMakeLists.txt can't find its source files -- which
# would break CMake's *entire* configure step for the whole workshop if it were
# wired into the shared build. So exercise 4 gets configured and built in its own
# isolated build directory instead.
#
# Usage:
#   ./build.bash --exercise <1-5> [--solution] [--clean]
#
# Examples:
#   ./build.bash --exercise 2             # build + run exercises/02_header_source_split
#   ./build.bash --exercise 2 --solution  # build + run solutions/02_header_source_split
#   ./build.bash --exercise 4             # configure + build exercises/04_project_layout in place
#   ./build.bash --exercise 3 --clean     # wipe the build dir first, then build + run exercise 3

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"

EXERCISES=(
  "01_single_file_class"
  "02_header_source_split"
  "03_wiring_header_files"
  "04_project_layout"
  "05_class_across_multiple_files"
)

usage() {
  cat <<EOF
Usage: $(basename "$0") --exercise <1-5> [--solution] [--clean]

  --exercise <1-5>   which classes exercise to build and run (required)
  --solution         build solutions/<name> instead of exercises/<name>
  --clean            wipe the build directory first, then reconfigure from scratch
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
  echo "error: --exercise <1-5> is required" >&2
  usage
  exit 1
fi

if ! [[ "${exercise_num}" =~ ^[1-5]$ ]]; then
  echo "error: --exercise must be a number from 1 to 5, got '${exercise_num}'" >&2
  exit 1
fi

name="${EXERCISES[$((exercise_num - 1))]}"

# --- Exercise 4: isolated mini project, built in its own directory ---------------
if [[ "${exercise_num}" == "4" ]]; then
  project_dir="${SCRIPT_DIR}/exercises/${name}"
  if [[ "${solution}" == true ]]; then
    project_dir="${SCRIPT_DIR}/solutions/${name}"
  fi
  local_build_dir="${project_dir}/build"

  if [[ "${clean}" == true ]]; then
    echo "Wiping ${local_build_dir}..."
    rm -rf "${local_build_dir}"
  fi

  echo "Configuring ${project_dir}..."
  if ! cmake -S "${project_dir}" -B "${local_build_dir}" >/dev/null; then
    echo ""
    echo "cmake couldn't configure ${name}. If this is the untouched exercise" \
         "(not --solution), that's expected -- it's telling you it can't find" \
         "src/ConeCounter.cpp and src/main.cpp yet, because you haven't moved" \
         "them there. See this section's README for the task."
    exit 1
  fi

  echo "Building ${name}..."
  if ! cmake --build "${local_build_dir}"; then
    echo "error: build failed" >&2
    exit 1
  fi

  echo ""
  echo "Running ${name}..."
  echo "----------------------------------------"
  "${local_build_dir}/${name}"
  exit $?
fi

# --- Exercises 1-3, 5: shared workshop build --------------------------------------
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
  echo ""
  echo "${target} failed to build. If this is an untouched exercise, that's" \
       "expected -- fix the compiler/linker errors above and run this again."
  exit 1
fi

echo ""
echo "Running ${target}..."
echo "----------------------------------------"
"${BUILD_DIR}/02-classes/${target}"
