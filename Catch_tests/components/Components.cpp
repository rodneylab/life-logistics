#include "components.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

constexpr float kFloatEps{0.001F};
constexpr float kFloatAbsMargin{0.000'001F};

TEST_CASE("MapTileDefaultConstructor", "MapTileTests")
{
    // arrange
    // act
    const MapTile map_tile{};

    // assert
    REQUIRE(map_tile.type == TileType::FLOOR);
}

TEST_CASE("PositionConstructors", "PositionTests")
{
    // arrange
    // act
    const Position position{};

    // assert
    REQUIRE_THAT(position.centre.x(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(position.centre.y(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));

    // arrange
    // act
    const Position position_1{Vector2D<float>{1.F, 2.F}};

    // assert
    REQUIRE_THAT(position_1.centre.x(),
                 Catch::Matchers::WithinRel(1.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.0F, kFloatAbsMargin));
    REQUIRE_THAT(position_1.centre.y(),
                 Catch::Matchers::WithinRel(2.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(2.0F, kFloatAbsMargin));

    // arrange
    // act
    const Position position_2{3.F, 4.F};

    // assert
    REQUIRE_THAT(position_2.centre.x(),
                 Catch::Matchers::WithinRel(3.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.0F, kFloatAbsMargin));
    REQUIRE_THAT(position_2.centre.y(),
                 Catch::Matchers::WithinRel(4.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(2.0F, kFloatAbsMargin));
}

TEST_CASE("RectangleConstructors", "RectangleTests")
{
    // arrange
    // act
    const RectangleComponent rectangle{};

    // assert
    REQUIRE(rectangle.colour().r == BLACK.r);
    REQUIRE(rectangle.colour().g == BLACK.g);
    REQUIRE(rectangle.colour().b == BLACK.b);
    REQUIRE(rectangle.colour().a == BLACK.a);
    REQUIRE(rectangle.width() == 0.F);
    REQUIRE(rectangle.height() == 0.F);

    // arrange
    // act
    const RectangleComponent rectangle_1{Vector2D{1.F, 2.F}, WHITE};

    // assert
    REQUIRE(rectangle_1.colour().r == WHITE.r);
    REQUIRE(rectangle_1.colour().g == WHITE.g);
    REQUIRE(rectangle_1.colour().b == WHITE.b);
    REQUIRE(rectangle_1.colour().a == WHITE.a);
    REQUIRE(rectangle_1.width() == 1.F);
    REQUIRE(rectangle_1.height() == 2.F);

    // arrange
    // act
    const RectangleComponent rectangle_2{3.F, 4.F, GRAY};

    // assert
    REQUIRE(rectangle_2.colour().r == GRAY.r);
    REQUIRE(rectangle_2.colour().g == GRAY.g);
    REQUIRE(rectangle_2.colour().b == GRAY.b);
    REQUIRE(rectangle_2.colour().a == GRAY.a);
    REQUIRE(rectangle_2.width() == 3.F);
    REQUIRE(rectangle_2.height() == 4.F);
}

TEST_CASE("VelocityConstructors", "VelocityTests")
{
    // arrange
    // act
    const Velocity velocity{};

    // assert
    REQUIRE_THAT(velocity.values.x(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(velocity.values.y(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));

    // arrange
    // act
    const Velocity velocity_1{1.F, 2.F};

    // assert
    REQUIRE_THAT(velocity_1.values.x(),
                 Catch::Matchers::WithinRel(1.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.0F, kFloatAbsMargin));
    REQUIRE_THAT(velocity_1.values.y(),
                 Catch::Matchers::WithinRel(2.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(2.0F, kFloatAbsMargin));
}
