#include "systems.h"

#include "components.h"
#include "constants.h"
#include "map.h"
#include "resources.h"
#include "vector2d.h"

#include <flecs/addons/cpp/entity.hpp>
#include <flecs/addons/cpp/mixins/query/impl.hpp>
#include <flecs/addons/cpp/world.hpp>

// Windows workarounds for CloseWindow / ShowCursor errors

#if defined(_WIN32)
#define NOGDI  // All GDI defines and routines
#define NOUSER // All USER defines and routines
#endif

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#undef near
#undef far

#include <raylib.h>

#include <cmath>
#include <string>
#include <string_view>

void draw_player_system(
    const flecs::query<const Player,
                       const RectangleComponent,
                       const Position,
                       const CameraResource> &draw_player_query)
{
    draw_player_query.each([](const Player & /* _player_tag */,
                              const RectangleComponent &rectangle,
                              const Position &position,
                              const CameraResource &camera) {
        DrawRectangle(
            static_cast<int>(std::round(position.centre.x() - camera.left() -
                                        rectangle.width() / 2.F)),
            static_cast<int>(std::round(position.centre.y() - camera.top() -
                                        rectangle.height() / 2.F)),
            static_cast<int>(std::round(rectangle.width())),
            static_cast<int>(std::round(rectangle.height())),
            rectangle.colour());
    });
}

void draw_tiles_system(
    const flecs::query<const MapTile,
                       const RectangleComponent,
                       const Position,
                       const CameraResource> &draw_tiles_query)
{
    draw_tiles_query.each([](const MapTile & /* _map_tile_tag */,
                             const RectangleComponent &rectangle,
                             const Position &position,
                             const CameraResource &camera) {
        const float tile_left{position.centre.x() - rectangle.width() / 2.F};
        const float tile_top{position.centre.y() - rectangle.height() / 2.F};
        const float tile_right{tile_left + rectangle.width()};
        const float tile_bottom{tile_top + rectangle.height()};
        if (camera.left() <= tile_right && tile_left <= camera.right() &&
            camera.top() <= tile_bottom && tile_top <= camera.bottom())
        {
            DrawRectangle(static_cast<int>(tile_left - camera.left()),
                          static_cast<int>(tile_top - camera.top()),
                          static_cast<int>(rectangle.width()),
                          static_cast<int>(rectangle.height()),
                          rectangle.colour());
        }
    });
}

void handle_player_input_system(
    const flecs::query<const Player, Velocity> &handle_player_input_query)
{
    handle_player_input_query.each(
        [](const Player & /* _player_tag */, Velocity &velocity) {
            velocity = {0.F, 0.F};

            if (IsKeyDown(KEY_W))
            {
                velocity.values.y(-constants::kPlayerSpeed);
                spdlog::trace("W key pressed");
            }
            if (IsKeyDown(KEY_A))
            {
                velocity.values.x(-constants::kPlayerSpeed);
                spdlog::trace("A key pressed");
            }
            if (IsKeyDown(KEY_S))
            {
                velocity.values.y(constants::kPlayerSpeed);
                spdlog::trace("S key pressed");
            }
            if (IsKeyDown(KEY_D))
            {
                velocity.values.x(constants::kPlayerSpeed);
                spdlog::trace("D key pressed");
            }
        });
}

flecs::entity spawn_player_system(const flecs::world &world)
{
    flecs::entity player_entity = world.entity();
    player_entity.add<Player>()
        .set<Position>(Position{
            0.F + static_cast<float>(constants::kTileDimensions.x()) / 2.F,
            0.F + static_cast<float>(constants::kTileDimensions.y()) / 2.F})
        .set<Velocity>({})
        .set<RectangleComponent>(
            {static_cast<float>(constants::kTileDimensions.x()),
             static_cast<float>(constants::kTileDimensions.y()),
             BLACK});

    return player_entity;
}

// Helper function
// name should be null-terminated
flecs::entity spawn_tile(const flecs::world &world,
                         const std::string_view &name,
                         const float left,
                         const float top,
                         const TileType tile_type,
                         const Color &tile_colour,
                         bool visible)
{
    const Vector2D<float> float_tile_dimensions{
        static_cast<float>(constants::kTileDimensions.x()),
        static_cast<float>(constants::kTileDimensions.y())};
    flecs::entity tile_entity =
        world
            .entity(name.data()) // safe if name is null-terminated
            //.is_a(MapTileEntity)
            .set<Position>(Position{Vector2D{left, top} +
                                    float_tile_dimensions /
                                        2.F}) // adjust this to give centre
            .set<RectangleComponent>({float_tile_dimensions, tile_colour})
            .set<MapTile>({tile_type});
    if (visible)
    {
        tile_entity.add<VisibleTile>();
    }
    return tile_entity;
}

void spawn_tiles_system(const flecs::world &world)
{
    const auto *camera = world.get<CameraResource>();
    const float camera_left{camera->left()};
    const float camera_right{camera->right()};
    const float camera_top{camera->top()};
    const float camera_bottom{camera->bottom()};

    constexpr wchar_t kU8MAX{256};
    for (int x_index{0}; x_index < world.get<Map>()->width(); ++x_index)
    {
        for (int y_index{0}; y_index < world.get<Map>()->height(); ++y_index)
        {
            const bool tile_visible{
                camera_left <= static_cast<float>(x_index) &&
                static_cast<float>(x_index) <= camera_right &&
                camera_top <= static_cast<float>(y_index) &&
                static_cast<float>(y_index) <= camera_bottom};

            const wchar_t tile_label{
                world.get<Map>()->get_tile(x_index, y_index)};
            const std::string name{
                fmt::format("Tile_{:03}_{:03}", x_index, y_index)};
            switch (tile_label)
            {
            case L'.':
                // empty space (floor)
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::FLOOR,
                           WHITE,
                           tile_visible);
                break;
            case L'#':
                // wall top
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::WALL,
                           BLUE,
                           tile_visible);
                break;
            case L'[':
                // wall left
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::WALL,
                           GREEN,
                           tile_visible);
                break;
            case L']':
                // wall right
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::WALL,
                           YELLOW,
                           tile_visible);
                break;
            case L'*':
                // locked door
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::DOOR,
                           RED,
                           tile_visible);
                break;
            case L'@':
                // collection point (incomplete)
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::COLLECTION,
                           PURPLE,
                           tile_visible);
                break;
            case L'C':
                // cargopod unlocked
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::CARGO,
                           PINK,
                           tile_visible);
                break;
            case L'?':
                // unlocked door
                spawn_tile(world,
                           name,
                           static_cast<float>(x_index *
                                              constants::kTileDimensions.x()),
                           static_cast<float>(y_index *
                                              constants::kTileDimensions.y()),
                           TileType::DOOR,
                           BROWN,
                           tile_visible);
                break;
            default:
                if (tile_label >= 0 && tile_label < kU8MAX)
                {
                    spdlog::error(
                        "Unhandled tile type found in map: `{}` at {},{}",
                        static_cast<char>(tile_label),
                        x_index,
                        y_index);
                }
                else
                {
                    spdlog::error("Unhandled tile type found in map at {},{}",
                                  x_index,
                                  y_index);
                }
                break;
            }
        }
    }
}

void update_camera_system(
    const flecs::query<const Player, CameraResource, const Map>
        &camera_update_query)
{
    camera_update_query.each([](flecs::entity entity,
                                const Player & /* _player_tag */,
                                CameraResource &camera,
                                const Map &map) {
        Vector2D<float> new_offset = Vector2D<float>{
            entity.get<Position>()->centre - camera.dimensions / 2.F};

        if (new_offset.x() < 0.F)
        {
            new_offset.x(0.F);
        }
        else if (new_offset.x() >
                 static_cast<float>(map.width()) - camera.dimensions.x())
        {
            new_offset.x(static_cast<float>(map.width()) -
                         camera.dimensions.x());
        }
        if (new_offset.y() < 0.F)
        {
            new_offset.y(0.F);
        }
        else if (new_offset.y() >
                 static_cast<float>(map.height()) - camera.dimensions.y())
        {
            new_offset.y(static_cast<float>(map.height()) -
                         camera.dimensions.y());
        }
        camera.offset = new_offset;
    });
}

void update_player_system(
    const flecs::query<const Player, const Velocity, Position>
        &update_player_query,
    const float frame_time)
{
    update_player_query.each([frame_time](const Player & /* _player_tag */,
                                          const Velocity &velocity,
                                          Position &position) {
        position.centre += velocity.values * frame_time;
    });
}
