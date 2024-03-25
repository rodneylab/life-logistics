
#include <utility>

#include "map.h"

struct LevelMap
{
    LevelMap() = default;

    explicit LevelMap(Map &map) : _map(map)
    //explicit LevelMap(Map map) : _map(std::move(map))
    {
    }

    Map _map;
};
