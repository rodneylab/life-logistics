#include "vector2d.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <sstream>

constexpr float kFloatEps{0.001F};
constexpr float kFloatAbsMargin{0.000'001F};

TEST_CASE("DefaultConstructor", "Vector2DTests")
{
    // arrange
    // act
    constexpr Vector2D<float> vec{};

    // assert
    REQUIRE_THAT(vec.x(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));
    REQUIRE_THAT(vec.y(),
                 Catch::Matchers::WithinRel(0.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.0F, kFloatAbsMargin));

    constexpr Vector2D<int> vec_int{};

    // assert
    REQUIRE(vec_int.x() == 0);
    REQUIRE(vec_int.y() == 0);
}

TEST_CASE("CopyConstructor", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec{1.F, 2.F};

    // act
    const Vector2D<float> vec_copy{vec};

    // assert
    REQUIRE(vec.x() == vec_copy.x());
    REQUIRE(vec.y() == vec_copy.y());

    // arrange
    const Vector2D<int> vec_int{1, 2};

    // act
    const Vector2D<int> vec_copy_int{vec_int};

    // assert
    REQUIRE(vec_int.x() == vec_copy_int.x());
    REQUIRE(vec_int.y() == vec_copy_int.y());
}

TEST_CASE("Mutators", "Vector2DTests")
{
    // arrange
    Vector2D<float> vec{1.F, 2.F};

    // act
    vec.x(3.F);
    vec.y(4.F);

    // assert
    REQUIRE(vec.x() == 3.F);
    REQUIRE(vec.y() == 4.F);

    // arrange
    Vector2D<int> vec_int{1, 2};

    // act
    vec_int.x(3);
    vec_int.y(4);

    // assert
    REQUIRE(vec_int.x() == 3);
    REQUIRE(vec_int.y() == 4);
}

TEST_CASE("UnaryMinusOperator", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec{1.F, 2.F};

    // act
    const Vector2D<float> vec_2{-vec};

    // assert
    REQUIRE(vec_2.x() == -vec.x());
    REQUIRE(vec_2.y() == -vec.y());

    // arrange
    Vector2D<int> vec_int{1, 2};

    // act
    const Vector2D<int> vec_int_2{-vec_int};

    // assert
    REQUIRE(vec_int_2.x() == -vec_int.x());
    REQUIRE(vec_int_2.y() == -vec_int.y());
}

TEST_CASE("AdditionAssignmentOperator", "Vector2DTests")
{
    // arrange
    Vector2D<float> vec{1.F, 2.F};
    const Vector2D<float> vec_2{3.F, 4.F};

    // act
    vec += vec_2;

    // assert
    REQUIRE_THAT(vec.x(),
                 Catch::Matchers::WithinRel(4.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(4.0F, kFloatAbsMargin));
    REQUIRE_THAT(vec.y(),
                 Catch::Matchers::WithinRel(6.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(6.0F, kFloatAbsMargin));

    // arrange
    Vector2D<int> vec_int{1, 2};
    const Vector2D<int> vec_int_2{3, 4};

    // act
    vec_int += vec_int_2;

    // assert
    REQUIRE(vec_int.x() == 4);
    REQUIRE(vec_int.y() == 6);
}

TEST_CASE("ConstantMultiplicationOperator", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec{1.F, 2.F};
    constexpr float factor{1.5F};

    // act
    const Vector2D<float> result{factor * vec};
    const Vector2D<float> result_2{vec * factor};

    // assert
    REQUIRE_THAT(result.x(),
                 Catch::Matchers::WithinRel(1.5F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.5F, kFloatAbsMargin));
    REQUIRE_THAT(result.y(),
                 Catch::Matchers::WithinRel(3.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(3.0F, kFloatAbsMargin));
    REQUIRE_THAT(result_2.x(),
                 Catch::Matchers::WithinRel(1.5F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.5F, kFloatAbsMargin));
    REQUIRE_THAT(result_2.y(),
                 Catch::Matchers::WithinRel(3.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(3.0F, kFloatAbsMargin));

    // arrange
    Vector2D<int> vec_int{1, 2};
    constexpr int factor_int{2};

    // act
    const Vector2D<int> result_int{factor_int * vec_int};
    const Vector2D<int> result_int_2{vec_int * factor_int};

    // assert
    REQUIRE(result_int.x() == 2);
    REQUIRE(result_int.y() == 4);
    REQUIRE(result_int_2.x() == 2);
    REQUIRE(result_int_2.y() == 4);
}

TEST_CASE("ConstantDivisionOperator", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec{1.F, 2.F};
    constexpr float divisor{2.F};

    // act
    const Vector2D<float> result{vec / divisor};

    // assert
    REQUIRE_THAT(result.x(),
                 Catch::Matchers::WithinRel(0.5F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(0.5F, kFloatAbsMargin));
    REQUIRE_THAT(result.y(),
                 Catch::Matchers::WithinRel(1.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(1.0F, kFloatAbsMargin));

    // arrange
    Vector2D<int> vec_int{1, 2};
    constexpr int divisor_int{2};

    // act
    const Vector2D<int> result_int{vec_int / divisor_int};

    // assert
    REQUIRE(result_int.x() == 0);
    REQUIRE(result_int.y() == 1);
}

TEST_CASE("OutputOperator", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec{1.F, 2.F};

    // act
    std::stringstream result;
    result << vec;

    // assert
    REQUIRE(result.str() == std::string{"1 2"});

    // arrange
    const Vector2D<int> vec_int{1, 2};

    // act
    std::stringstream result_int;
    result_int << vec_int;

    // assert
    REQUIRE(result_int.str() == std::string{"1 2"});
}

TEST_CASE("Addition", "Vector2DTests")
{
    // arrange
    const Vector2D<float> vec_1{1.F, 2.F};
    const Vector2D<float> vec_2{3.F, 4.F};

    // act
    const Vector2D<float> result{vec_1 + vec_2};

    // assert
    REQUIRE_THAT(result.x(),
                 Catch::Matchers::WithinRel(4.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(4.0F, kFloatAbsMargin));
    REQUIRE_THAT(result.y(),
                 Catch::Matchers::WithinRel(6.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(6.0F, kFloatAbsMargin));

    // arrange
    const Vector2D<int> vec_1_int{1, 2};
    const Vector2D<int> vec_2_int{3, 4};

    // act
    const Vector2D<int> result_int{vec_1_int + vec_2_int};

    // assert
    REQUIRE(result_int.x() == 4);
    REQUIRE(result_int.y() == 6);
}

TEST_CASE("Subtraction", "Vector2DTests")
{
    // arrange
    Vector2D<float> vec_1{1.F, 2.F};
    Vector2D<float> vec_2{3.F, 4.F};

    // act
    Vector2D<float> result{vec_1 - vec_2};

    // assert
    REQUIRE_THAT(result.x(),
                 Catch::Matchers::WithinRel(-2.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(-2.0F, kFloatAbsMargin));
    REQUIRE_THAT(result.y(),
                 Catch::Matchers::WithinRel(-2.F, kFloatEps) ||
                     Catch::Matchers::WithinAbs(-2.0F, kFloatAbsMargin));

    // arrange
    Vector2D<int> vec_1_int{1, 2};
    Vector2D<int> vec_2_int{3, 4};

    // act
    Vector2D<int> result_int{vec_1_int - vec_2_int};

    // assert
    REQUIRE(result_int.x() == -2);
    REQUIRE(result_int.y() == -2);
}
