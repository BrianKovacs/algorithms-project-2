
# Requires the `cmake` command to be at least version 2.8.
cmake_minimum_required(VERSION 2.8)


# Declares the project name and its implementation language. "CXX"
# means "C++".
project(pgm-compressor CXX)


# Update the C++ compiler flags so that we use C++11, not the older
# version of the language, C++03. GCC-4.9, the default compiler in
# our labs works with this setting. So does the default compiler on
# an up-to-date Mac OS X system.
set(CMAKE_CXX_FLAGS -std=c++11)


# Declare that we want to build an executable program named "run".
add_executable(pgm-compressor main.cpp)
