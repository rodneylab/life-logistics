#include "queries.h"
#include "systems.h"

#include <catch2/catch_test_macros.hpp>
//#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>

//constexpr float kFloatEps{0.001F};
//constexpr float kFloatAbsMargin{0.000'001F};

TEST_CASE("QueryHelperFunctions", "QueriesTests")
{
    // arrange
    const flecs::world world;
    const float frame_time{1.F / 60.F};

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

    // assert
    REQUIRE_NOTHROW(camera_update_query.each(
        [](flecs::entity entity,
           const Player & /* _player_tag */,
           CameraResource &camera,
           const Map &map) { std::cout << "Test\n"; }));
    REQUIRE_NOTHROW(draw_player_query.each(
        [](const Player & /* _player_tag */,
           const RectangleComponent &rectangle,
           const Position &position,
           const CameraResource &camera) { std::cout << "Test\n"; }));
    REQUIRE_NOTHROW(draw_tiles_query.each(
        [](const MapTile & /* _map_tile_tag */,
           const RectangleComponent &rectangle,
           const Position &position,
           const CameraResource &camera) { std::cout << "Test\n"; }));
    REQUIRE_NOTHROW(handle_player_input_query.each(
        [](const Player & /* _player_tag */, Velocity &velocity) {
            std::cout << "Test\n";
        }));
    REQUIRE_NOTHROW(
        update_player_query.each([frame_time](const Player & /* _player_tag */,
                                              const Velocity &velocity,
                                              Position &position) {
            position.centre += velocity.values * frame_time;
        }));
}
