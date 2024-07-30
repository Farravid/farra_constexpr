cmake_minimum_required(VERSION 3.2)
project(interval_map VERSION 1.0)

# Variables
set(PROJECT_NAME_TEST interval_map_test)
set(PROJECT_NAME_BENCHMARK interval_map_benchmark)

# This actually overrides the value from conan
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Useful for visual code intelissense on Linux
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME_TEST} test/main.cpp)
add_executable(${PROJECT_NAME_BENCHMARK} benchmark/main.cpp)

find_package(Boost REQUIRED)
find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

target_include_directories(${PROJECT_NAME_TEST} PUBLIC src)
target_include_directories(${PROJECT_NAME_BENCHMARK} PUBLIC src)

target_link_libraries(${PROJECT_NAME} boost::boost)
target_link_libraries(${PROJECT_NAME_TEST} gtest::gtest)
target_link_libraries(${PROJECT_NAME_BENCHMARK} boost::boost)
target_link_libraries(${PROJECT_NAME_BENCHMARK} benchmark::benchmark_main)