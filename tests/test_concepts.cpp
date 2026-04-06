#include "algebra_concepts.hpp"
#include "complex.hpp"
#include <iostream>

static_assert(Group<Complex>, "Complex class must satisfy the Group concept requirements!");
static_assert(Ring<Complex>, "Complex class must satisfy the Ring concept requirements!");
static_assert(Field<Complex>, "Complex class must satisfy the Field concept requirements!");

int main() {
    std::cout << "SUCCESS: All compile-time algebraic checks passed!" << std::endl;
    std::cout << "  ✓ Complex is a Group" << std::endl;
    std::cout << "  ✓ Complex is a Ring" << std::endl;
    std::cout << "  ✓ Complex is a Field" << std::endl;
    return 0;
}
