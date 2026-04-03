cmake_minimum_required(VERSION 3.15)
project(PaddyMath VERSION 1.0 LANGUAGES C CXX ASM)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(test_concepts
    src/complex.cpp
    tests/test_concepts.cpp
    # Later, you'll add your Matrix.cpp or .s files here
)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    target_compile_options(test_concepts PRIVATE -march=native -O3)
endif()