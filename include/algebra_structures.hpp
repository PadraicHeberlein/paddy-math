#ifndef ALGEBRA_STRUCTURES_HPP
#define ALGEBRA_STRUCTURES_HPP

/**
 * @brief Base interfaces for algebraic structures using CRTP (Curiously Recurring Template Pattern).
 * This maintains high performance by avoiding virtual function overhead while providing a 
 * formal inheritance hierarchy as requested.
 */

template <typename Derived>
struct GroupInterface {
    protected:
        GroupInterface() = default;
};

template <typename Derived>
struct RingInterface : public GroupInterface<Derived> {
    protected:
        RingInterface() = default;
};

template <typename Derived>
struct FieldInterface : public RingInterface<Derived> {
    protected:
        FieldInterface() = default;
};

template <typename Derived, typename Scalar = double>
struct VectorSpaceInterface : public GroupInterface<Derived> {
    protected:
        VectorSpaceInterface() = default;
};

#endif // ALGEBRA_STRUCTURES_HPP
