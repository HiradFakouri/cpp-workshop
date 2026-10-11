#!/usr/bin/env bash
# Every exercise in this section is its own self-contained mini project, each
# with its own CMakeLists.txt (or, for exercises 1-3, no CMakeLists.txt yet --
# writing one is the exercise). None of them share the workshop-wide build/ dir
# from earlier sections, because writing/fixing that file IS the point here.
#
# Usage:
#   ./build.bash --exercise <1-4> [--solution] [--clean]
#
# Examples:
#   ./build.bash --exercise 1             # configure + build exercises/01_your_first_cmakelists
#   ./build.bash --exercise 1 --solution  # same, but the finished reference version
#   ./build.bash --exercise 4 --clean     # wipe that exercise's build dir first

set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

EXERCISES=(
  "01_your_first_cmakelists"
  "02_multi_file_project"
  "03_building_a_library"
  "04_fix_the_build"
)

usage() {
  cat <<EOF
Usage: $(basename "$0") --exercise <1-4> [--solution] [--clean]

  --exercise <1-4>   which cmake exercise to configure and build (required)
  --solution         build solutions/<name> instead of exercises/<name>
  --clean            wipe that exercise's build directory first
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
project_dir="${SCRIPT_DIR}/exercises/${name}"
if [[ "${solution}" == true ]]; then
  project_dir="${SCRIPT_DIR}/solutions/${name}"
fi
build_dir="${project_dir}/build"

if [[ "${clean}" == true ]]; then
  echo "Wiping ${build_dir}..."
  rm -rf "${build_dir}"
fi

if [[ ! -f "${project_dir}/CMakeLists.txt" ]]; then
  echo "No CMakeLists.txt in ${project_dir} yet."
  if [[ "${solution}" == true ]]; then
    echo "That shouldn't happen for --solution -- something's wrong with the workshop itself." >&2
    exit 1
  fi
  echo "That's the exercise: write one. See this section's README for what it needs to do."
  exit 1
fi

echo "Configuring ${project_dir}..."
if ! cmake -S "${project_dir}" -B "${build_dir}" >/dev/null; then
  echo ""
  echo "cmake couldn't configure ${name}. If you just wrote or edited" \
       "CMakeLists.txt, the error above is telling you what's wrong with it."
  exit 1
fi

echo "Building ${name}..."
if ! cmake --build "${build_dir}"; then
  echo ""
  echo "Build failed. Read the error above -- it'll say whether this is a" \
       "compiler error (a #include the compiler can't find, usually a missing" \
       "target_include_directories) or a linker error (usually a missing" \
       "target_link_libraries)."
  exit 1
fi

echo ""
echo "Running ${name}..."
echo "----------------------------------------"
"${build_dir}/${name}"
