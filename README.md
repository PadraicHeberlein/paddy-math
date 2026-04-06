# 🧮 PaddyMath: High-Performance C++ Math Library

A state-of-the-art C++ mathematical library specializing in complex numbers and matrix computations, optimized for modern ARM architectures. PaddyMath bridges high-level C++20 abstractions with high-performance low-level kernels.

---

## ⚡ Key Features

*   **🛡️ C++20 Algebraic Concepts**: Type-safe template constraints ensuring only valid algebraic structures can be used in computations.
*   **🏎️ ARM A64/NEON Optimization**: High-performance backend utilizing SIMD (Single Instruction, Multiple Data) through NEON assembly for heavy numerical tasks.
*   **📐 Advanced Numerical Stability**: Implementation of **Scaling & Squaring** for matrix exponentials, preventing divergence and ensuring precision for large inputs.
*   **⚖️ Unified C/C++ Backend**: A stable C-backend seamlessly integrated with a modern C++ frontend.

---

## 📁 Repository Structure

```text
paddy-math/
├── include/                # Header files (.hpp, .h)
│   ├── algebra_concepts.hpp # C++20 template constraints
│   ├── algebra_functions.hpp # Generic algebraic functions (Taylor)
│   ├── complex.hpp          # Complex number class
│   ├── matrix.hpp           # Template matrix class
│   └── math_backend.h       # C interface for numerical kernels
├── src/                    # Source files (.cpp, .c, .S)
│   ├── complex.cpp         # Complex class implementation
│   ├── math_backend.c      # Numerical core in C
│   └── arm_kernel.S        # ARM A64/NEON Assembly kernels
├── tests/                  # Unit tests
│   ├── test_complex.cpp
│   ├── test_concepts.cpp
│   ├── test_library.cpp
│   └── test_matrix.cpp
└── CMakeLists.txt         # Build system configuration
```

---

## 🛠️ Build & Installation

PaddyMath uses **CMake** as its build system. Follow these steps to build the project and its test suite:

### Prerequisites
- **CMake** (v3.15 or higher)
- **C++ Compiler** (supporting C++20, e.g., GCC 10+ or Clang 10+)
- **Make** (standard build utility)

### 1. Configure the Build
Create a build directory to keep the source tree clean:
```bash
mkdir -p build
cd build
cmake ..
```

### 2. Compile with Make
Once configured, use `make` to compile the executables:
```bash
make
```
This will generate the following test binaries in the `build` directory:
- `test_concepts`
- `test_complex`
- `test_matrix`
- `test_library`

---

## 🧪 Running Tests

After a successful build, you can run the test suite directly from the `build` directory:

```bash
./test_concepts
./test_complex
./test_matrix
./test_library
```

---

## 💡 Optimization Note
On ARM-based systems (like Raspberry Pi 4), PaddyMath automatically detects the architecture and enables `-march=native -O3` optimizations along with the custom ARM Assembly kernels for maximum throughput.

---
*Created with ❤️ by Antigravity*
