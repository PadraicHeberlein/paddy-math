#ifndef REAL_HPP
#define REAL_HPP

#include <iostream>
#include <variant>
#include <cstdint>
#include "algebra_structures.hpp"

/**
 * @brief Internal FixedPoint storage for the Real class.
 * Provides runtime-configurable fixed-point arithmetic.
 */
struct FixedStorage {
    int64_t raw;
    int frac_bits;

    static FixedStorage from_double(double val, int bits);
    double to_double() const;

    FixedStorage operator-() const;
    FixedStorage operator+(const FixedStorage& other) const;
    FixedStorage operator-(const FixedStorage& other) const;
    FixedStorage operator*(const FixedStorage& other) const;
    FixedStorage operator/(const FixedStorage& other) const;
    bool operator==(const FixedStorage& other) const;
};

/**
 * @brief Unified Real class that acts as a wrapper for different numerical backends.
 */
class Real : public FieldInterface<Real> {
public:
    enum class Type {
        Float,
        Double,
        Fixed32,
        Fixed64,
        CustomFixed
    };

    struct Options {
        Type type;
        int custom_bits = 0;

        static Options Float() { return { Type::Float }; }
        static Options Double() { return { Type::Double }; }
        static Options Fixed32() { return { Type::Fixed32 }; }
        static Options Fixed64() { return { Type::Fixed64 }; }
        static Options Fixed(int bits) { return { Type::CustomFixed, bits }; }
    };

private:
    std::variant<float, double, FixedStorage> storage;

public:
    // Constructors
    Real(double val = 0.0, Options opt = Options::Double());

    // Helper to get as double
    double to_double() const;

    // Operators
    Real operator-() const;
    Real operator+(const Real& other) const;
    Real operator-(const Real& other) const;
    Real operator*(const Real& other) const;
    Real operator/(const Real& other) const;

    // Comparison
    bool operator==(const Real& other) const;
    bool operator!=(const Real& other) const;

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Real& r);

    // Explicit conversion for convenience
    operator double() const;
};

/**
 * @brief Norm function for the Real class.
 * Satisfies the NormedAlgebra concept.
 */
double norm(const Real& r);

/**
 * @brief Absolute value function for the Real class.
 */
Real abs(const Real& r);

#endif // REAL_HPP
