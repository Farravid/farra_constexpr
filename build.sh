conan install . --build=missing -pr=./conan_profile
cd build/Release
source ./generators/conanbuild.sh
cmake ../.. -DCMAKE_TOOLCHAIN_FILE="generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Release"
cmake --build .
./interval_map

# See a way to launch only test, benchmark, all...
#./interval_map_test

#./interval_map_benchmark