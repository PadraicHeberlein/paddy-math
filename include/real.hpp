#ifndef REAL_HPP
#define REAL_HPP

#include <iostream>
#include <variant>
#include <type_traits>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include "algebra_structures.hpp"

/**
 * @brief Internal FixedPoint storage for the Real class.
 * Provides runtime-configurable fixed-point arithmetic.
 */
struct FixedStorage {
    int64_t raw;
    int frac_bits;

    static FixedStorage from_double(double val, int bits) {
        return { static_cast<int64_t>(std::round(val * (1LL << bits))), bits };
    }

    double to_double() const {
        return static_cast<double>(raw) / (1LL << frac_bits);
    }

    FixedStorage operator-() const { return { -raw, frac_bits }; }

    FixedStorage operator+(const FixedStorage& other) const {
        // Simple case: same fractional bits
        if (frac_bits == other.frac_bits) return { raw + other.raw, frac_bits };
        // Mixed case: promote to higher precision
        int max_bits = std::max(frac_bits, other.frac_bits);
        int64_t r1 = raw << (max_bits - frac_bits);
        int64_t r2 = other.raw << (max_bits - other.frac_bits);
        return { r1 + r2, max_bits };
    }

    FixedStorage operator-(const FixedStorage& other) const {
        int max_bits = std::max(frac_bits, other.frac_bits);
        int64_t r1 = raw << (max_bits - frac_bits);
        int64_t r2 = other.raw << (max_bits - other.frac_bits);
        return { r1 - r2, max_bits };
    }

    FixedStorage operator*(const FixedStorage& other) const {
        __int128_t res = (static_cast<__int128_t>(raw) * other.raw) >> other.frac_bits;
        return { static_cast<int64_t>(res), frac_bits };
    }

    FixedStorage operator/(const FixedStorage& other) const {
        __int128_t res = (static_cast<__int128_t>(raw) << other.frac_bits) / other.raw;
        return { static_cast<int64_t>(res), frac_bits };
    }

    bool operator==(const FixedStorage& other) const {
        if (frac_bits == other.frac_bits) return raw == other.raw;
        return to_double() == other.to_double(); // Fallback for mixed
    }
};

/**
 * @brief Unified Real class that acts as a wrapper for different numerical backends.
 * 
 * This class provides a single interface for floating-point and fixed-point arithmetic,
 * allowing the representation to be chosen at runtime during construction.
 */
class Real : public FieldInterface<Real> {
public:
    enum class Type {
        Float,
        Double,
        Fixed32, // Preset: 32-bit (16 fractional)
        Fixed64, // Preset: 64-bit (32 fractional)
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
    Real(double val = 0.0, Options opt = Options::Double()) {
        switch (opt.type) {
            case Type::Float:  storage = static_cast<float>(val); break;
            case Type::Double: storage = val; break;
            case Type::Fixed32: storage = FixedStorage::from_double(val, 16); break;
            case Type::Fixed64: storage = FixedStorage::from_double(val, 32); break;
            case Type::CustomFixed: storage = FixedStorage::from_double(val, opt.custom_bits); break;
        }
    }

    // Helper to get as double
    double to_double() const {
        return std::visit([](auto&& arg) -> double {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, FixedStorage>) return arg.to_double();
            else return static_cast<double>(arg);
        }, storage);
    }

    // Unary minus
    Real operator-() const {
        return std::visit([](auto&& arg) -> Real {
            Real res;
            res.storage = -arg; // FixedStorage supports -
            return res;
        }, storage);
    }

    // Arithmetic operators
    Real operator+(const Real& other) const {
        // If they have the same variant index, we can perform direct arithmetic
        if (storage.index() == other.storage.index()) {
            return std::visit([&](auto&& lhs) -> Real {
                using T = std::decay_t<decltype(lhs)>;
                Real res;
                res.storage = lhs + std::get<T>(other.storage);
                return res;
            }, storage);
        }
        // Mixed arithmetic: promote to double
        return Real(this->to_double() + other.to_double());
    }

    Real operator-(const Real& other) const {
        if (storage.index() == other.storage.index()) {
            return std::visit([&](auto&& lhs) -> Real {
                using T = std::decay_t<decltype(lhs)>;
                Real res;
                res.storage = lhs - std::get<T>(other.storage);
                return res;
            }, storage);
        }
        return Real(this->to_double() - other.to_double());
    }

    Real operator*(const Real& other) const {
        if (storage.index() == other.storage.index()) {
            return std::visit([&](auto&& lhs) -> Real {
                using T = std::decay_t<decltype(lhs)>;
                Real res;
                res.storage = lhs * std::get<T>(other.storage);
                return res;
            }, storage);
        }
        return Real(this->to_double() * other.to_double());
    }

    Real operator/(const Real& other) const {
        if (storage.index() == other.storage.index()) {
            return std::visit([&](auto&& lhs) -> Real {
                using T = std::decay_t<decltype(lhs)>;
                Real res;
                res.storage = lhs / std::get<T>(other.storage);
                return res;
            }, storage);
        }
        return Real(this->to_double() / other.to_double());
    }

    // Comparison
    bool operator==(const Real& other) const {
        if (storage.index() == other.storage.index()) {
            return std::visit([&](auto&& lhs) -> bool {
                using T = std::decay_t<decltype(lhs)>;
                return lhs == std::get<T>(other.storage);
            }, storage);
        }
        return to_double() == other.to_double();
    }

    bool operator!=(const Real& other) const { return !(*this == other); }

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Real& r) {
        std::visit([&os](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, FixedStorage>) os << arg.to_double();
            else os << arg;
        }, r.storage);
        return os;
    }

    // Explicit conversion for convenience
    operator double() const { return to_double(); }
};

#endif // REAL_HPP
