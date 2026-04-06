#include "real.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <variant>

// --- FixedStorage Implementation ---

FixedStorage FixedStorage::from_double(double val, int bits) {
    if (bits < 0 || bits > 62) throw std::invalid_argument("Fractional bits must be between 0 and 62");
    return { static_cast<int64_t>(std::round(val * (1ULL << bits))), bits };
}

double FixedStorage::to_double() const {
    return static_cast<double>(raw) / (static_cast<double>(1ULL << frac_bits));
}

FixedStorage FixedStorage::operator-() const {
    return { -raw, frac_bits };
}

FixedStorage FixedStorage::operator+(const FixedStorage& other) const {
    if (frac_bits == other.frac_bits) return { raw + other.raw, frac_bits };
    int max_bits = std::max(frac_bits, other.frac_bits);
    int64_t r1 = raw << (max_bits - frac_bits);
    int64_t r2 = other.raw << (max_bits - other.frac_bits);
    return { r1 + r2, max_bits };
}

FixedStorage FixedStorage::operator-(const FixedStorage& other) const {
    if (frac_bits == other.frac_bits) return { raw - other.raw, frac_bits };
    int max_bits = std::max(frac_bits, other.frac_bits);
    int64_t r1 = raw << (max_bits - frac_bits);
    int64_t r2 = other.raw << (max_bits - other.frac_bits);
    return { r1 - r2, max_bits };
}

FixedStorage FixedStorage::operator*(const FixedStorage& other) const {
    __int128_t res = (static_cast<__int128_t>(raw) * other.raw) >> other.frac_bits;
    return { static_cast<int64_t>(res), frac_bits };
}

FixedStorage FixedStorage::operator/(const FixedStorage& other) const {
    if (other.raw == 0) throw std::runtime_error("FixedStorage: Division by zero");
    __int128_t res = (static_cast<__int128_t>(raw) << other.frac_bits) / other.raw;
    return { static_cast<int64_t>(res), frac_bits };
}

bool FixedStorage::operator==(const FixedStorage& other) const {
    if (frac_bits == other.frac_bits) return raw == other.raw;
    return to_double() == other.to_double();
}

// --- Real Implementation ---

Real::Real(double val, Options opt) {
    switch (opt.type) {
        case Type::Float:  storage = static_cast<float>(val); break;
        case Type::Double: storage = val; break;
        case Type::Fixed32: storage = FixedStorage::from_double(val, 16); break;
        case Type::Fixed64: storage = FixedStorage::from_double(val, 32); break;
        case Type::CustomFixed: storage = FixedStorage::from_double(val, opt.custom_bits); break;
    }
}

double Real::to_double() const {
    return std::visit([](auto&& arg) -> double {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, FixedStorage>) return arg.to_double();
        else return static_cast<double>(arg);
    }, storage);
}

Real Real::operator-() const {
    Real res = *this;
    res.storage = std::visit([](auto&& arg) -> std::variant<float, double, FixedStorage> {
        return -arg;
    }, storage);
    return res;
}

Real Real::operator+(const Real& other) const {
    if (storage.index() == other.storage.index()) {
        Real res = *this;
        res.storage = std::visit([&](auto&& lhs) -> std::variant<float, double, FixedStorage> {
            using T = std::decay_t<decltype(lhs)>;
            return lhs + std::get<T>(other.storage);
        }, storage);
        return res;
    }
    return Real(this->to_double() + other.to_double());
}

Real Real::operator-(const Real& other) const {
    if (storage.index() == other.storage.index()) {
        Real res = *this;
        res.storage = std::visit([&](auto&& lhs) -> std::variant<float, double, FixedStorage> {
            using T = std::decay_t<decltype(lhs)>;
            return lhs - std::get<T>(other.storage);
        }, storage);
        return res;
    }
    return Real(this->to_double() - other.to_double());
}

Real Real::operator*(const Real& other) const {
    if (storage.index() == other.storage.index()) {
        Real res = *this;
        res.storage = std::visit([&](auto&& lhs) -> std::variant<float, double, FixedStorage> {
            using T = std::decay_t<decltype(lhs)>;
            return lhs * std::get<T>(other.storage);
        }, storage);
        return res;
    }
    return Real(this->to_double() * other.to_double());
}

Real Real::operator/(const Real& other) const {
    if (storage.index() == other.storage.index()) {
        Real res = *this;
        res.storage = std::visit([&](auto&& lhs) -> std::variant<float, double, FixedStorage> {
            using T = std::decay_t<decltype(lhs)>;
            return lhs / std::get<T>(other.storage);
        }, storage);
        return res;
    }
    return Real(this->to_double() / other.to_double());
}

bool Real::operator==(const Real& other) const {
    if (storage.index() == other.storage.index()) {
        return std::visit([&](auto&& lhs) -> bool {
            using T = std::decay_t<decltype(lhs)>;
            return lhs == std::get<T>(other.storage);
        }, storage);
    }
    return to_double() == other.to_double();
}

bool Real::operator!=(const Real& other) const {
    return !(*this == other);
}

Real::operator double() const {
    return to_double();
}

std::ostream& operator<<(std::ostream& os, const Real& r) {
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, FixedStorage>) os << arg.to_double();
        else os << arg;
    }, r.storage);
    return os;
}

double norm(const Real& r) {
    return std::abs(r.to_double());
}

Real abs(const Real& r) {
    return Real(std::abs(r.to_double()));
}
