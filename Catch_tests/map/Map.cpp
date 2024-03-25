#include "map.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

constexpr float kFloatEps{0.001F};
constexpr float kFloatAbsMargin{0.000'001F};

TEST_CASE("MapDefaultConstructor", "MapTests")
{
    // arrange
    // act
    const Map map{};

    // assert
    REQUIRE(map.width() == 0);
    REQUIRE(map.height() == 0);
}

TEST_CASE("MapInitialise", "MapTests")
{
    // arrange
    Map map{};

    // act
    map.initialise();

    // assert
    REQUIRE(map.width() == 64);
    REQUIRE(map.height() == 29);
    REQUIRE(map.dimensions().x() == 64);
    REQUIRE(map.dimensions().y() == 29);
}

TEST_CASE("MapSetGetTile", "MapTests")
{
    // arrange
    Map map{};
    map.initialise();

    // act
    map.set_tile(1, 2, L'#');
    const wchar_t result{map.get_tile(1, 2)};

    // assert
    REQUIRE(result == L'#');

    // act
    map.set_tile(1, 2, L'[');
    const wchar_t result_1{map.get_tile(1, 2)};

    // assert
    REQUIRE(result_1 == L'[');

    REQUIRE_THROWS_AS(map.get_tile(-1, 10), std::out_of_range);
    REQUIRE_THROWS_WITH(map.get_tile(10, -1),
                        "Attempt at out-of-bounds access on level map");
    REQUIRE_THROWS_AS(map.set_tile(999, 10, L'!'), std::out_of_range);
    REQUIRE_THROWS_WITH(map.set_tile(0, 999, L'!'),
                        "Attempt at out-of-bounds access on level map");
}
