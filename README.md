# 🧮 PaddyMath: High-Performance C++ Math Library

A state-of-the-art C++ mathematical library specializing in complex numbers and matrix computations, optimized for modern ARM architectures. PaddyMath bridges high-level C++20 abstractions with high-performance low-level kernels.

---

## ⚡ Key Features

*   **🛡️ C++20 Algebraic Concepts**: Type-safe template constraints ensuring only valid algebraic structures can be used in computations.
*   **🏎️ ARM & RISC-V Optimization**: High-performance backends utilizing SIMD through NEON (ARM) and RISC-V assembly kernels for heavy numerical tasks.
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
│   └── pm_math.h            # C interface for numerical kernels
├── src/                    # Source files (.cpp, .c, .S)
│   ├── complex.cpp         # Complex number class implementation
│   ├── matrix.cpp          # Matrix class implementation
│   ├── algebra_functions.cpp
│   ├── algebra_structures.cpp
│   └── backend/
│       ├── pm_math.c       # Numerical core in C
│       ├── arm/
│       │   └── math_kernel.s # ARM A64/NEON Assembly kernels
│       └── riscv/
│           └── math_kernel.s # RISC-V Vector/Assembly kernels
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

## 🚀 Command Line Interface (CLI)

PaddyMath includes a powerful CLI for quick calculations from your terminal.

### Building the CLI
The CLI is automatically built when you follow the standard installation steps:
```bash
cd build
make pm-cli
```

### Usage Examples
You can use the CLI for both complex numbers and matrix operations:

#### 🟢 Complex Numbers
Calculate the exponential of a complex number:
```bash
./pm-cli complex --real 1.0 --imag 1.5
```

#### 🟡 Matrix Operations
Calculate the matrix exponential for a 2x2 matrix:
```bash
./pm-cli matrix --elements 1 2 3 4
```

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
On ARM and RISC-V systems (e.g., Raspberry Pi 4 or VisionFive 2), PaddyMath automatically detects the architecture and enables `-march=native -O3` optimizations along with the custom assembly kernels for maximum throughput.

---
*Created with ❤️ by Antigravity*
