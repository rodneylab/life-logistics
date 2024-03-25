#include "vector2d.h"

/*! \file src/vector2d.cpp
 * \brief Defintions for lightweight two-dimensional vector class, using STD array for data storage.  Accepts template parameter for the data class.  Intended for use with small, basic types (bool, int, float double etc.).
 */

template <typename T>
Vector2D<T>::Vector2D(const T x_value, const T y_value)
    : elements{x_value, y_value}
{
}

template <typename T>
Vector2D<T>::Vector2D(const Vector2D &other) : elements(other.elements)
{
}

template <typename T>
Vector2D<T>::Vector2D(Vector2D &&other) noexcept
    : elements(std::move(other.elements))
{
}

template <typename T>
[[nodiscard]] T Vector2D<T>::x() const
{
    return elements[0];
}

template <typename T>
[[nodiscard]] T Vector2D<T>::y() const
{
    return elements[1];
}

template <typename T>
void Vector2D<T>::x(const T x_value)
{
    elements[0] = x_value;
}

template <typename T>
void Vector2D<T>::y(const T y_value)
{
    elements[1] = y_value;
}

template <typename T>
Vector2D<T> &Vector2D<T>::operator=(const Vector2D &other)
{
    if (this != &other)
    {
        elements = other.elements;
    }
    return *this;
}

template <typename T>
Vector2D<T> &Vector2D<T>::operator=(Vector2D &&other) noexcept
{
    elements = std::move(other.elements);
    return *this;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-() const
{
    return {-elements[0], -elements[1]};
}

template <typename T>
Vector2D<T> &Vector2D<T>::operator+=(const Vector2D &other)
{
    elements[0] += other.elements[0];
    elements[1] += other.elements[1];

    return *this;
}
