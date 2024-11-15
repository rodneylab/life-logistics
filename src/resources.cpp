
#include <utility>

#include "map.h"

struct LevelMap
{
    LevelMap() = default;

    explicit LevelMap(Map &map) : _map(map)
    {
    }

    Map _map;
};
