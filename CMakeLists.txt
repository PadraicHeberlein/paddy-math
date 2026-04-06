cmake_minimum_required(VERSION 3.15)
project(PaddyMath VERSION 1.0 LANGUAGES C CXX ASM)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Prefer using target_include_directories for each target to be explicit
add_executable(test_concepts tests/test_concepts.cpp src/complex.cpp)
target_include_directories(test_concepts PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(test_complex tests/test_complex.cpp src/complex.cpp)
target_include_directories(test_complex PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    target_compile_options(test_concepts PRIVATE -march=native -O3)
endif()