target_binary=--target=interval_map
target_name=interval_map

target_interval=
target_interval_test=
target_interval_benchmark=

build_type=Release

if [[ "$1" == "benchmark" ]];
then
    target_binary=$target_binary"_benchmark"
    target_interval_benchmark=./interval_map_benchmark
elif [[ "$1" == "test" ]];
then
    target_binary=$target_binary"_test"
    target_interval_test=./interval_map_test
elif [[ "$1" == "all" ]];
then
    target_binary=
    target_interval_benchmark=./interval_map_benchmark
    target_interval_test=./interval_map_test
    target_interval=./interval_map
else
    target_interval=./interval_map
fi

if [[ "$2" == "Debug" ]];
then
    build_type=Debug
fi

conan install conan/ --build=missing -pr=./conan/conan_profile --settings=build_type=$build_type
cd build/$build_type
source ./generators/conanbuild.sh
cmake ../.. -DCMAKE_TOOLCHAIN_FILE="generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="$build_type"
cmake --build . $target_binary

$target_interval
$target_interval_test
$target_interval_benchmark