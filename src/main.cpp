#include "constants.h"
#include "map.h"
#include "queries.h" // NOLINT [misc-include-cleaner]
#include "resources.h"
#include "systems.h"

#include <flecs/addons/cpp/flecs.hpp>
#include <flecs/addons/cpp/world.hpp>
#include <spdlog/cfg/env.h>

#include <raylib.h>

int main()
{
    spdlog::cfg::
        load_env_levels(); // use `export SPDLOG_LEVEL=trace` to set log level from command line

    InitWindow(constants::kWindowWidth,
               constants::kWindowHeight,
               constants::kWindowTitle.data());
    InitAudioDevice();

    SetTargetFPS(constants::kTargetFramerate);

    const flecs::world world;

    // Initialise resources (singletons)
    Map level_map{};
    level_map.initialise();
    world.set<Map>({level_map});
    world.set<CameraResource>({});

    spawn_tiles_system(world);
    spawn_player_system(world);

    const auto camera_update_query = get_camera_update_query(world);
    const auto draw_player_query = get_draw_player_query(world);
    const auto draw_tiles_query = get_draw_tiles_query(world);
    const auto handle_player_input_query = get_handle_player_input_query(world);
    const auto update_player_query = get_update_player_query(world);

    while (!WindowShouldClose())
    {
        const float frame_time{GetFrameTime()};

        handle_player_input_system(handle_player_input_query);
        update_camera_system(camera_update_query);

        update_player_system(update_player_query, frame_time);

        BeginDrawing();

        ClearBackground(BLACK);

        draw_tiles_system(draw_tiles_query);
        draw_player_system(draw_player_query);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
