cmake_minimum_required(VERSION 3.10)
project(PaddyMath)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add our header-only library
add_library(paddy_math INTERFACE)
target_include_directories(paddy_math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
