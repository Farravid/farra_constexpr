cmake_minimum_required(VERSION 3.15)
project(interval_map)

# This actually overrides the value from conan
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} src/interval_map.cpp)

target_link_libraries(${PROJECT_NAME} benchmark::benchmark_main)
target_link_libraries(${PROJECT_NAME} gtest::gtest)