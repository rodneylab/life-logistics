#ifndef SRC_VECTOR2D_H
#define SRC_VECTOR2D_H

/*! \file src/vector2d.h
 * \brief Defintions for lightweight two-dimensional vector class, using STD array for data storage.  Accepts template parameter for the data class.  Intended for use with small, basic types (bool, int, float double etc.).
 */

#include <array>

template <typename T>
class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(T x_value, T y_value);
    Vector2D(const Vector2D &other);
    Vector2D(Vector2D &&other) noexcept;
    ~Vector2D() = default;

    // manipulators
    [[nodiscard]] T x() const;
    [[nodiscard]] T y() const;

    // mutators
    void x(T x_value);
    void y(T y_value);

    Vector2D<T> &operator=(const Vector2D &other);
    Vector2D<T> &operator=(Vector2D &&other) noexcept;
    Vector2D<T> operator-() const;
    Vector2D<T> &operator+=(const Vector2D &other);

private:
    std::array<T, 2> elements;
};

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const Vector2D<T> &value)
{
    return out << value.x() << ' ' << value.y();
}

template <typename T>
inline Vector2D<T> operator+(const Vector2D<T> &value_u,
                             const Vector2D<T> &value_v)
{
    return {
        value_u.x() + value_v.x(),
        value_u.y() + value_v.y(),
    };
}

template <typename T>
inline Vector2D<T> operator-(const Vector2D<T> &value_u,
                             const Vector2D<T> &value_v)
{
    return {
        value_u.x() - value_v.x(),
        value_u.y() - value_v.y(),
    };
}

template <typename T>
inline Vector2D<T> operator*(const T value_t, const Vector2D<T> &value_v)
{
    return {
        value_t * value_v.x(),
        value_t * value_v.y(),
    };
}

template <typename T>
inline Vector2D<T> operator*(const Vector2D<T> &value_v, const T value_t)
{
    return {value_t * value_v};
}

template <typename T>
inline Vector2D<T> operator/(const Vector2D<T> &value_v, const T value_t)
{
    return {value_v.x() / value_t, value_v.y() / value_t};
}

#endif
