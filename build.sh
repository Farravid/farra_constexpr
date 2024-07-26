rm -rf build

conan install . --output-folder=build --build=missing -pr=./conan_profile
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Release"
cmake --build .
./interval_map