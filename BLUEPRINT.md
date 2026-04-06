# 💎 PADDY MATH LIBRARY BLUEPRINT

## ⚙️ Low-Level Specifications
We aim for **PaddyMath** to be a fast, efficient, and versatile mathematical library suitable for a broad spectrum of computing—from 8-bit microcontrollers to 64-bit supercomputers. 
- **Modern Standards**: The library is built using **C++20** and leverages modern language features.
- **Universal Architecture**: We support **x86/Intel**, **ARM**, **RISC-V**, **MIPS**, and other architectures as they emerge.
- **Endian & Word Independence**: The codebase is designed to run seamlessly on both 32-bit and 64-bit systems, and handles both little-endian and big-endian memory layouts.
- **Optimized Dispatch**: Our evolving set of functions is accessible through both C and C++ interfaces. These interfaces intelligently select the optimal assembly kernel for the host architecture to maximize performance.

## 🧮 High-Level Specifications
For transcendental functions, we implement them using **Taylor series expansion** by treating the input as a vector space. This architectural choice allows us to use a single, unified implementation of the $(x^n)/n!$ term for varied algebraic structures, including real numbers, complex numbers, and matrices.

## 🎯 Design Principles
Our development focus is twofold:
1.  **State-of-the-Art Implementation**: We implement the best-known numerical methods for any given use case to ensure maximum precision and performance.
2.  **Scientific Evolution**: We prioritize building modular pathways to integrate new discoveries in numerical methods, ensuring **PaddyMath** remains at the cutting edge of library-compatible mathematical software.