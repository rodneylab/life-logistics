#include "map.h"

#include "constants.h"
#include "vector2d.h"

#include <spdlog/spdlog.h>

#include <cstddef>
#include <stdexcept>
#include <string>

const Vector2D<int> &Map::dimensions() const
{
    return _dimensions;
}

int Map::width() const
{
    return _dimensions.x();
}

int Map::height() const
{
    return _dimensions.y();
}

wchar_t Map::get_tile(int x_index, int y_index) const
{
    if (x_index >= 0 && x_index < _dimensions.x() && y_index >= 0 &&
        y_index < _dimensions.y())
    {
        return _data[static_cast<size_t>(y_index) *
                         static_cast<size_t>(_dimensions.x()) +
                     static_cast<size_t>(x_index)];
    }
    // out-of-bounds element
    spdlog::error("Attempt at out-of-bounds element access on level "
                  "map({},{}): `{},{}`",
                  width(),
                  height(),
                  x_index,
                  y_index);
    throw std::out_of_range("Attempt at out-of-bounds access on level map");
};

void Map::set_tile(int x_index, int y_index, wchar_t value)
{
    if (x_index >= 0 && x_index < _dimensions.x() && y_index >= 0 &&
        y_index < _dimensions.y())
    {
        _data[static_cast<size_t>(y_index) *
                  static_cast<size_t>(_dimensions.x()) +
              static_cast<size_t>(x_index)] = value;
    }
    else
    {
        // out-of-bounds element
        spdlog::error("Attempt at out-of-bounds element access "
                      "on level  map({},{}): `{},{}`",
                      _dimensions.x(),
                      _dimensions.y(),
                      x_index,
                      y_index);
        throw std::out_of_range("Attempt at out-of-bounds access on level map");
    }
};

void Map::initialise()
{
    _dimensions =
        Vector2D<int>{constants::kLevelWidth, constants::kLevelHeight};
    _data.reserve(static_cast<size_t>(width()) * static_cast<size_t>(height()));
    _data = std::wstring{};

    // row-first encoding
    _data +=
        L"[################################]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[######################*#########]#############################]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................*.............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[................................].............................]";
    _data +=
        L"[######################*#########]#############################]";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[................................]..............................";
    _data +=
        L"[################################]..............................";
}
