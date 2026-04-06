/**
 * @file algebra_structures.cpp
 * @brief Implementation unit for the CRTP algebraic interface hierarchy.
 *
 * All interfaces (GroupInterface, RingInterface, FieldInterface,
 * VectorSpaceInterface, AlgebraInterface, NormedAlgebraInterface) are
 * fully header-defined CRTP structs with protected constructors and no
 * virtual functions, so there are no out-of-line method bodies to define.
 *
 * This translation unit exists to:
 *   1. Provide an explicit compilation check that the header is
 *      self-contained and parseable in isolation.
 *   2. Force concrete instantiations of each interface tier so that
 *      the linker sees them and any future out-of-line additions are
 *      caught early.
 */

#include "../include/algebra_structures.hpp"

// ---------------------------------------------------------------------------
// Concrete "probe" types — one per interface level.
// Each inherits from the relevant interface so the compiler verifies the
// entire CRTP chain compiles without errors.
// ---------------------------------------------------------------------------

namespace {

/// Minimal Group: addition, subtraction, negation, equality.
struct ProbeGroup : GroupInterface<ProbeGroup> {
    ProbeGroup() = default;
    ProbeGroup operator+(const ProbeGroup&) const { return {}; }
    ProbeGroup operator-(const ProbeGroup&) const { return {}; }
    ProbeGroup operator-()                  const { return {}; }
    bool operator==(const ProbeGroup&)      const { return true; }
    bool operator!=(const ProbeGroup&)      const { return false; }
};

/// Minimal Ring: Group + multiplication + unity.
struct ProbeRing : RingInterface<ProbeRing> {
    ProbeRing() = default;
    explicit ProbeRing(int)  {}   // T(0), T(1)
    explicit ProbeRing(double) {} // scalar construction
    ProbeRing operator+(const ProbeRing&) const { return {}; }
    ProbeRing operator-(const ProbeRing&) const { return {}; }
    ProbeRing operator-()                 const { return {}; }
    ProbeRing operator*(const ProbeRing&) const { return {}; }
    bool operator==(const ProbeRing&)     const { return true; }
    bool operator!=(const ProbeRing&)     const { return false; }
};

/// Minimal Field: Ring + division.
struct ProbeField : FieldInterface<ProbeField> {
    ProbeField() = default;
    explicit ProbeField(int)    {}
    explicit ProbeField(double) {}
    ProbeField operator+(const ProbeField&) const { return {}; }
    ProbeField operator-(const ProbeField&) const { return {}; }
    ProbeField operator-()                  const { return {}; }
    ProbeField operator*(const ProbeField&) const { return {}; }
    ProbeField operator/(const ProbeField&) const { return {}; }
    bool operator==(const ProbeField&)      const { return true; }
    bool operator!=(const ProbeField&)      const { return false; }
};

/// Minimal VectorSpace: Group + scalar multiplication / division.
struct ProbeVectorSpace : VectorSpaceInterface<ProbeVectorSpace, double> {
    ProbeVectorSpace() = default;
    ProbeVectorSpace operator+(const ProbeVectorSpace&) const { return {}; }
    ProbeVectorSpace operator-(const ProbeVectorSpace&) const { return {}; }
    ProbeVectorSpace operator-()                        const { return {}; }
    ProbeVectorSpace operator*(double)                  const { return {}; }
    ProbeVectorSpace operator/(double)                  const { return {}; }
    friend ProbeVectorSpace operator*(double, const ProbeVectorSpace& v) { return v; }
    bool operator==(const ProbeVectorSpace&) const { return true; }
    bool operator!=(const ProbeVectorSpace&) const { return false; }
};

/// Minimal Algebra: Ring ∩ VectorSpace.
struct ProbeAlgebra : AlgebraInterface<ProbeAlgebra, double> {
    ProbeAlgebra() = default;
    explicit ProbeAlgebra(int)    {}
    explicit ProbeAlgebra(double) {}
    ProbeAlgebra operator+(const ProbeAlgebra&) const { return {}; }
    ProbeAlgebra operator-(const ProbeAlgebra&) const { return {}; }
    ProbeAlgebra operator-()                    const { return {}; }
    ProbeAlgebra operator*(const ProbeAlgebra&) const { return {}; }
    ProbeAlgebra operator*(double)              const { return {}; }
    ProbeAlgebra operator/(double)              const { return {}; }
    friend ProbeAlgebra operator*(double, const ProbeAlgebra& a) { return a; }
    bool operator==(const ProbeAlgebra&) const { return true; }
    bool operator!=(const ProbeAlgebra&) const { return false; }
};

/// Minimal NormedAlgebra: Algebra + norm.
struct ProbeNormedAlgebra : NormedAlgebraInterface<ProbeNormedAlgebra, double> {
    ProbeNormedAlgebra() = default;
    explicit ProbeNormedAlgebra(int)    {}
    explicit ProbeNormedAlgebra(double) {}
    ProbeNormedAlgebra operator+(const ProbeNormedAlgebra&) const { return {}; }
    ProbeNormedAlgebra operator-(const ProbeNormedAlgebra&) const { return {}; }
    ProbeNormedAlgebra operator-()                          const { return {}; }
    ProbeNormedAlgebra operator*(const ProbeNormedAlgebra&) const { return {}; }
    ProbeNormedAlgebra operator*(double)                    const { return {}; }
    ProbeNormedAlgebra operator/(double)                    const { return {}; }
    friend ProbeNormedAlgebra operator*(double, const ProbeNormedAlgebra& a) { return a; }
    bool operator==(const ProbeNormedAlgebra&) const { return true; }
    bool operator!=(const ProbeNormedAlgebra&) const { return false; }
    friend double norm(const ProbeNormedAlgebra&) { return 0.0; }
};

} // namespace
