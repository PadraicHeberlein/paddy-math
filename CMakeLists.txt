cmake_minimum_required(VERSION 3.15)
project(PaddyMath VERSION 1.0 LANGUAGES C CXX ASM)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch CLI11 for the CLI tool
include(FetchContent)
FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(cli11)

# Determine architecture and common sources
set(COMMON_SRCS
    src/complex.cpp
    src/matrix.cpp
    src/algebra_functions.cpp
    src/algebra_structures.cpp
    src/real.cpp
    src/backend/pm_math.c
)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm")
    list(APPEND COMMON_SRCS src/backend/arm/math_kernel.s)
    add_definitions(-DARCH_ARM)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "riscv64|riscv32")
    list(APPEND COMMON_SRCS src/backend/riscv/math_kernel.s)
    add_definitions(-DARCH_RISCV)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i386")
    list(APPEND COMMON_SRCS src/backend/x86/math_kernel.s)
    add_definitions(-DARCH_X86)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "mips")
    list(APPEND COMMON_SRCS src/backend/mips/math_kernel.s)
    add_definitions(-DARCH_MIPS)
endif()

# Define the core library
add_library(paddy_math ${COMMON_SRCS})
target_include_directories(paddy_math PUBLIC ${CMAKE_SOURCE_DIR}/include)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm|riscv64|riscv32|x86_64|amd64|i386|mips")
    target_compile_options(paddy_math PRIVATE -march=native -O3)
endif()

# --- Tests ---
add_executable(test_concepts tests/test_concepts.cpp)
target_link_libraries(test_concepts PRIVATE paddy_math)

add_executable(test_complex tests/test_complex.cpp)
target_link_libraries(test_complex PRIVATE paddy_math)

add_executable(test_matrix tests/test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE paddy_math)

add_executable(test_library tests/test_library.cpp)
target_link_libraries(test_library PRIVATE paddy_math)

add_executable(test_real tests/test_real.cpp)
target_link_libraries(test_real PRIVATE paddy_math)

# --- CLI Tool ---
add_executable(pm-cli tools/pm-cli.cpp)
target_link_libraries(pm-cli PRIVATE paddy_math CLI11::CLI11)