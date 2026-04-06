#include "algebra_concepts.hpp"
#include "complex.hpp"
#include <iostream>

// This line will fail to compile if Complex is NOT a Group
static_assert(Group<Complex>, "Complex class must satisfy the Group concept requirements!");

int main() {
    std::cout << "Compile-time check passed: Complex is a valid Group!" << std::endl;
    return 0;
}
