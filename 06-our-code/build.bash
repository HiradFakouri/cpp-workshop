#!/usr/bin/env bash
# Wrapper around the CMake build documented in the top-level README. Same
# shared build/ dir as sections 1, 2, and 4 for exercises 1-2. Exercise 3 has
# no code -- there's nothing to build -- so --exercise 3 just opens the
# question file instead.
#
# Usage:
#   ./build.bash --exercise <1-3> [--solution] [--clean]
#
# Examples:
#   ./build.bash --exercise 1             # build + run exercises/01_real_structures.cpp
#   ./build.bash --exercise 2 --solution  # build + run solutions/02_eigen_basics.cpp
#   ./build.bash --exercise 3             # print exercises/03_finding_things/QUESTIONS.md

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build"

EXERCISES=(
  "01_real_structures"
  "02_eigen_basics"
  "03_finding_things"
)

usage() {
  cat <<EOF
Usage: $(basename "$0") --exercise <1-3> [--solution] [--clean]

  --exercise <1-3>   which our-code exercise to build and run (required)
  --solution         build solutions/<name>.cpp instead of exercises/<name>.cpp
                      (exercise 3: show solutions/03_finding_things/ANSWERS.md)
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
  echo "error: --exercise <1-3> is required" >&2
  usage
  exit 1
fi

if ! [[ "${exercise_num}" =~ ^[1-3]$ ]]; then
  echo "error: --exercise must be a number from 1 to 3, got '${exercise_num}'" >&2
  exit 1
fi

name="${EXERCISES[$((exercise_num - 1))]}"

# --- Exercise 3: no code, just print the question/answer file ------------------
if [[ "${exercise_num}" == "3" ]]; then
  if [[ "${solution}" == true ]]; then
    cat "${SCRIPT_DIR}/solutions/03_finding_things/ANSWERS.md"
  else
    cat "${SCRIPT_DIR}/exercises/03_finding_things/QUESTIONS.md"
  fi
  exit 0
fi

# --- Exercises 1-2: shared workshop build ---------------------------------------
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
       "expected -- fix the compiler errors above and run this again."
  exit 1
fi

echo ""
echo "Running ${target}..."
echo "----------------------------------------"
"${BUILD_DIR}/06-our-code/${target}"
