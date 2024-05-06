TARGET_BUILD_DIR="build"

rm -rf "${TARGET_BUILD_DIR}"


cmake -B "${TARGET_BUILD_DIR}" -S .
cmake --build "${TARGET_BUILD_DIR}"
