#include "systems.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

constexpr float kFloatEps{0.001F};
constexpr float kFloatAbsMargin{0.000'001F};

TEST_CASE("SpawnPlayerSystemHelperFunctions", "SystemsTests")
{
    // arrange
    const flecs::world world;

    // act
    const flecs::entity player_entity{spawn_player_system(world)};

    // assert
    REQUIRE_THAT(player_entity.get<Position>()->centre.x(),
                 Catch::Matchers::WithinRel(8.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(player_entity.get<Position>()->centre.y(),
                 Catch::Matchers::WithinRel(8.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(player_entity.get<Velocity>()->values.x(),
                 Catch::Matchers::WithinRel(0.0F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(player_entity.get<Velocity>()->values.y(),
                 Catch::Matchers::WithinRel(0.0F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(player_entity.get<RectangleComponent>()->width(),
                 Catch::Matchers::WithinRel(16.0F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(16.0F, kFloatAbsMargin));
    REQUIRE_THAT(player_entity.get<RectangleComponent>()->height(),
                 Catch::Matchers::WithinRel(16.0F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(16.0F, kFloatAbsMargin));
    REQUIRE(player_entity.get<RectangleComponent>()->colour().r == BLACK.r);
    REQUIRE(player_entity.get<RectangleComponent>()->colour().g == BLACK.g);
    REQUIRE(player_entity.get<RectangleComponent>()->colour().b == BLACK.b);
    REQUIRE(player_entity.get<RectangleComponent>()->colour().a == BLACK.a);
}
