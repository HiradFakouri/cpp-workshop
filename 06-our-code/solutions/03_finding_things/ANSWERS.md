# Exercise 3: answers

Don't read this until you've actually tried the questions in
`exercises/03_finding_things/QUESTIONS.md` yourself. The answer without the
search isn't the skill this exercise is drilling.

1. **`src/FastSLAM2/Association.cpp`**. The doc comment above
   `_associateLandmark` says why: each particle's landmark map is private to
   that particle and only ever has on the order of a hundred to a few hundred
   cones by the end of a lap, which a plain scan with a cheap distance
   pre-filter handles comfortably. There's no shared map across particles to
   index, since every particle is now a full particle with its own map.
   Found with: `grep -rn "_associateLandmark" src/`

2. **`LocalObservation`** is declared in
   `include/ugrdv_mapping/FastSLAM2/FastSLAM2.hpp`. Its other three fields:
   `localX`, `localY`, and `colour` (all alongside `colourProbability`).
   Found with: `grep -rn "colourProbability" include/`

3. **`SLAM`**: a library (`add_library(SLAM ...)`), not the `ugrdv_mapping`
   executable. The executable links against `SLAM` instead of Eigen
   directly:
   ```cmake
   target_link_libraries(SLAM
       OpenMP::OpenMP_CXX
       Eigen3::Eigen
       ${ugrdv_common_LIBRARIES}
   )
   ```
   Found with: `grep -n "Eigen3::Eigen" CMakeLists.txt`

4. **9 files**: `Association.cpp`, `BatchUpdate.cpp`, `Diagnostics.cpp`,
   `FastSLAM2.cpp`, `PoseEstimation.cpp`, `Prediction.cpp`, `Proposal.cpp`,
   `Resampling.cpp`, `Trajectory.cpp`.
   Found with: `grep -rl "FastSLAM2::" src/FastSLAM2/`

5. **`src/main.cpp`**. Besides creating the node and spinning it, it also:
   parses `--rosbag`/`--output-csv` command-line arguments (before
   `rclcpp::init()` consumes `argv`), can replay a rosbag through SLAM
   directly instead of running the node normally (`pNode->runRosbag(bagPath)`),
   writes the resulting trajectory/map to a CSV file, and launches a
   plotting script to visualise it when replaying a bag.
   Found with: `cat src/main.cpp` (it's short enough to just read end to end).

← [Back to workshop overview](../../../README.md)
