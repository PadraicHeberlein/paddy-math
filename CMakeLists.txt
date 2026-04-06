cmake_minimum_required(VERSION 3.15)
project(PaddyMath VERSION 1.0 LANGUAGES C CXX ASM)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Determine architecture and common sources
set(COMMON_SRCS src/complex.cpp src/math_backend.c src/matrix.cpp src/algebra_functions.cpp)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    list(APPEND COMMON_SRCS src/arm_kernel.S)
    add_definitions(-DARCH_ARM)
endif()

add_executable(test_concepts tests/test_concepts.cpp ${COMMON_SRCS})
target_include_directories(test_concepts PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(test_complex tests/test_complex.cpp ${COMMON_SRCS})
target_include_directories(test_complex PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(test_matrix tests/test_matrix.cpp ${COMMON_SRCS})
target_include_directories(test_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    target_compile_options(test_matrix PRIVATE -march=native -O3)
endif()

add_executable(test_library tests/test_library.cpp ${COMMON_SRCS})
target_include_directories(test_library PRIVATE ${CMAKE_SOURCE_DIR}/include)