# farra_constexpr
This is a compilation of handy constexpr utilities for C++23.
You can check individual usage and uses of each utility in the specific docs listed.

> This is just a learning project, nothing fancy production ready. Use it at your own risk and enjoy! 
> 
Because we love compile time programming 😎 

# Utilities
* [farra::function](docs/function.md)
* [farra::flat_interval_map](docs/interval_map.md)


# Setup
> For a header only setup you can switch to the include branch

After cloning the repo, you only need to build the project with the handy bash script.

This is the synstax for `build.sh` 
```bash
./build.sh [target, default=interval_map] [build_type, default=Release]
```
So these are all the targets available
```bash
./build.sh test #will execute the tests
./build.sh benchmark #will execute the benchmarks
./build.sh all #will execute all
```
Remember you can add Debug after the target name in order to build the debug libraries 

## Dependencies
* C++23
* GCC 14.1
* Conan 2.0
* CMake 3.2

# What did I refresh/learn?
* **C++**
  * `constexpr`
    * `std::vector and std::unique_ptr`
  * Data structures
  * `<ranges>`
  * `<concepts>`
  * C++23 deducing `this`
  * Perfect forwarding (`std::forward`)
  * Lifetime of objects (thanks to `lifeobject.hpp`)
  * CTAD
  * Type erasure (`std::function`)
* **Tools and libraries**
  * Google benchmark library
  * Google test library (gtest)
  * Conan package manager
  * CMake 