#ifndef SRC_QUERIES_H
#define SRC_QUERIES_H

/*! \file src/queries.h
 * \brief Declarations ECS query getter utility functions
 */

#include "components.h"
#include "constants.h"
#include "map.h"
#include "resources.h"

#include <flecs.h> // NOLINT [misc-include-cleaner]
#include <flecs/addons/cpp/mixins/query/impl.hpp>

#include <cmath>

const flecs::query<const Player, CameraResource, const Map>
get_camera_update_query(const flecs::world &world)
{
    return world.query_builder<const Player, CameraResource, const Map>()
        .term_at(2)
        .singleton()
        .term_at(3)
        .singleton()
        .build();
}

const flecs::query<const Player,
                   const RectangleComponent,
                   const Position,
                   const CameraResource>
get_draw_player_query(const flecs::world &world)
{
    return world
        .query_builder<const Player,
                       const RectangleComponent,
                       const Position,
                       const CameraResource>()
        .term_at(4)
        .singleton()
        .build();
}

const flecs::query<const MapTile,
                   const RectangleComponent,
                   const Position,
                   const CameraResource>
get_draw_tiles_query(const flecs::world &world)
{
    return world
        .query_builder<const MapTile,
                       const RectangleComponent,
                       const Position,
                       const CameraResource>()
        .term_at(4)
        .singleton()
        .build();
}

const flecs::query<const Player, Velocity> get_handle_player_input_query(
    const flecs::world &world)
{
    return world.query_builder<const Player, Velocity>().build();
}

const flecs::query<const Player, const Velocity, Position>
get_update_player_query(const flecs::world &world)
{
    return world.query_builder<const Player, const Velocity, Position>()
        .build();
}

#endif
