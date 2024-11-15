#ifndef SRC_COMPONENTS_H
#define SRC_COMPONENTS_H

/*! \file src/components.h
 * \brief Declarations for ECS component classes and structs.
 */

#include "vector2d.h"

#include <raylib.h>

/**
 * \brief Class enum used for by drawing and collision systems.
 */
enum class TileType
{
    FLOOR,
    WALL,
    DOOR,
    CARGO,
    COLLECTION,
    UNLOCKED_DOOR
};

/**
 * \brief MapTile ECS component struct, used for drawing tiles.
 */
struct MapTile
{
    MapTile() = default;

    /**
 * \brief Tiles default to FLOOR type.
 */
    TileType type{TileType::FLOOR};
};

/**
 * \brief Player ECS tag.
 */
struct Player
{
};

/**
 * \brief VisibleTile ECS tag, intended for use with tile drawing system, for efficient rendering of large maps.
 */
struct VisibleTile
{
};

/**
 * \brief Position ECS component struct, used in drawing and collision systems.
 *
 * \note The centre is stored, rather that the top-left corner (used for raylib rendering).  Also, the value is stored as  `float` here, while RayLib uses `int` for drawing.  Coordinates are map-based (not camera-based).
 */
struct Position
{
    /**
     * \brief Default constructor initialises centre to `(0.0, 0.0)`.
     * */
    Position() : centre{}
    {
    }

    /**
     * \brief Constructor initialising with a two-dimensional vector.
     *
     * \param[in] position_vector   A Vector2D<float> containing the `x`,`y` coordinates of the centre of the related entity.
     */
    explicit Position(const Vector2D<float> &position_vector)
        : centre{position_vector}
    {
    }

    /**
     * \brief Constructor initialising with x, y coordinates.
     *
     * \param[in] centre_x   `x` coordinate for the centre of the related entity.
     * \param[in] centre_y   `y` coordinate for the centre of the related entity.
     */
    Position(const float centre_x, const float centre_y)
        : centre{centre_x, centre_y}
    {
    }

    Vector2D<float> centre;
};

/**
 * \brief Rectangle ECS component struct, with size and colour data. Used in drawing system.  Width and height are stored as floats,with pixel units.  The colour uses the raylib format.
 */
class RectangleComponent
{
public:
    /**
     * \brief Default constructor initialises size to ``0.0`` by ``0.0`` and colour to BLACK.
     * */
    RectangleComponent() : dimensions{}, _colour{BLACK}
    {
    }

    /**
     * \brief Constructor taking dimensions as a Vector2D (width is the first vector element and height the second).
     * \param[in] dimensions_value  Vector2D<float> with width and height of the related entity.
     * \param[in] colour_value      Colour that should be used for painting the related entity, using the raylib Color struct format.
     */
    RectangleComponent(const Vector2D<float> &dimensions_value,
                       const Color colour_value)
        : dimensions{dimensions_value}, _colour{colour_value}
    {
    }

    /**
     * \brief Constructor taking individual dimension values.
     * \param[in] width_value   Width of the related entity.
     * \param[in] height_value  Height of the related entity.
     * \param[in] colour_value  Colour that should be used for painting the related entity, using the raylib Color struct format.
     */
    RectangleComponent(const float width_value,
                       const float height_value,
                       const Color colour_value)
        : dimensions{width_value, height_value}, _colour{colour_value}
    {
    }

    RectangleComponent(const RectangleComponent &other) = default;
    RectangleComponent(RectangleComponent &&other) = default;
    RectangleComponent &operator=(const RectangleComponent &other) = default;
    RectangleComponent &operator=(RectangleComponent &&other) = default;
    ~RectangleComponent() = default;

    /**
     * \brief Width accessor method.
     * \return   Width of the rectangle component.
     */
    [[nodiscard]] float width() const
    {
        return dimensions.x();
    }

    /**
     * \brief Height accessor method.
     * \return   Height of the rectangle component.
     */
    [[nodiscard]] float height() const
    {
        return dimensions.y();
    }

    /**
     * \brief Colour accessor method.
     * \return   Colour of the rectangle component as a raylib Color struct.
     */
    [[nodiscard]] const Color &colour() const
    {
        return _colour;
    }

private:
    Vector2D<float> dimensions;
    Color _colour;
};

/**
 * \brief Velocity ECS component struct, used in movement systems. Units are pixels per second.
 *
 */
struct Velocity
{
    /**
     * \brief Default constructor initialises velocity to 0.0 in the ``x`` and ``y`` directions.
     * */
    Velocity() : values{}
    {
    }

    /**
     * \brief Constructor initialising with a two-dimensional vector.
     *
     * \param[in] other-values   A Vector2D<float> containing the `x`,`y` velocity of the related entity.
     */
    explicit Velocity(const Vector2D<float> &other_values)
        : values{other_values}
    {
    }

    /**
     * \brief Constructor initialising with separate x and y values.
     *
     * \param[in] velocity_x   The `x`-direction velocity of the related entity.
     * \param[in] velocity_y   The `y`-direction velocity of the related entity.
     */
    Velocity(const float velocity_x, const float velocity_y)
        : values{velocity_x, velocity_y}
    {
    }

    Vector2D<float> values;
};

#endif
