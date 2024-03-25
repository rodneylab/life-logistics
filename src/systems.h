#ifndef SRC_SYSTEMS_H
#define SRC_SYSTEMS_H

/*! \file src/systems.h
 * \brief Declarations for ECS system execution functions
 */

#include "components.h"
#include "resources.h"

#include <flecs.h> // NOLINT [misc-include-cleaner]
#include <flecs/addons/cpp/flecs.hpp>
#include <flecs/addons/cpp/mixins/system/impl.hpp>
#include <flecs/addons/cpp/world.hpp>

void draw_player_system(
    const flecs::query<const Player,
                       const RectangleComponent,
                       const Position,
                       const CameraResource> &draw_player_query);

void draw_tiles_system(
    const flecs::query<const MapTile,
                       const RectangleComponent,
                       const Position,
                       const CameraResource> &draw_tiles_query);

void handle_player_input_system(
    const flecs::query<const Player, Velocity> &handle_player_input_query);

flecs::entity spawn_player_system(const flecs::world &world);
void spawn_tiles_system(const flecs::world &world);

void update_camera_system(
    const flecs::query<const Player, CameraResource, const Map>
        &camera_update_query);
void update_player_system(
    const flecs::query<const Player, const Velocity, Position>
        &update_player_query,
    const float frame_time);

#endif
