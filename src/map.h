#ifndef SRC_MAP_H
#define SRC_MAP_H

/*! \file src/map.h
 * \brief Declarations level map for level map class
 */

#include "vector2d.h"

#include <string>

class Map
{
public:
    Map() : _dimensions{}
    {
    }

    Map(const Map &other) = default;
    Map(Map &&other) = default;
    Map &operator=(const Map &other) = default;
    Map &operator=(Map &&other) = default;
    ~Map() = default;

    // accessors
    [[nodiscard]] const Vector2D<int> &dimensions() const;

    // manipulators
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;

    [[nodiscard]] wchar_t get_tile(int x_index, int y_index) const;

    // mutators
    void initialise();
    void set_tile(int x_index, int y_index, wchar_t value);

private:
    Vector2D<int> _dimensions;
    std::wstring _data{};
};

#endif
