#ifndef SRC_VECTOR2D_H
#define SRC_VECTOR2D_H

/*! \file src/vector2d.h
 * \brief Definitions for lightweight two-dimensional vector class, using STD array for data storage.  Accepts template parameter for the data class.  Intended for use with small, basic types (bool, int, float double etc.).
 */

#include <array>
#include <ostream>

#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#define VECTOR2D_EXPORTS
#define VECTOR2D_NO_EXPORT
#else
#ifndef VECTOR2D_EXPORTS
#ifdef Vector2D_lib_EXPORTS
/* We are building this library */
#define VECTOR2D_EXPORTS
#else
/* We are using this library */
#define VECTOR2D_EXPORTS
#endif
#endif

#ifndef VECTOR2D_NO_EXPORT
#define VECTOR2D_NO_EXPORT
#endif
#endif

#ifndef VECTOR2D_DEPRECATED
#define VECTOR2D_DEPRECATED __attribute__((__deprecated__))
#endif

#ifndef VECTOR2D_DEPRECATED_EXPORT
#define VECTOR2D_DEPRECATED_EXPORT VECTOR2D_EXPORTS VECTOR2D_DEPRECATED
#endif

#ifndef VECTOR2D_DEPRECATED_NO_EXPORT
#define VECTOR2D_DEPRECATED_NO_EXPORT VECTOR2D_NO_EXPORT VECTOR2D_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#ifndef VECTOR2D_NO_DEPRECATED
#define VECTOR2D_NO_DEPRECATED
#endif
#endif

template <typename T>
class VECTOR2D_EXPORTS Vector2D
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
