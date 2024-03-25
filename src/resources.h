#ifndef SRC_RESOURCES_H
#define SRC_RESOURCES_H

/*! \file src/resources.h
 * \brief Declarations for ECS resources (singletons)
 */

#include "constants.h"
#include "map.h"

#include <raylib.h>

#include <utility>

struct CameraResource
{
    [[nodiscard]] float left() const
    {
        return offset.x();
    }

    [[nodiscard]] float right() const
    {
        return offset.x() +
               dimensions.x() *
                   static_cast<float>(constants::kTileDimensions.x());
    }

    [[nodiscard]] float top() const
    {
        return offset.y();
    }

    [[nodiscard]] float bottom() const
    {
        return offset.y() +
               dimensions.y() *
                   static_cast<float>(constants::kTileDimensions.y());
    }

    Vector2D<float> offset{0.F, 0.F};
    Vector2D<float> dimensions{
        static_cast<float>(GetScreenWidth()) /
            static_cast<float>(constants::kTileDimensions.x()),
        static_cast<float>(GetScreenHeight()) /
            static_cast<float>(constants::kTileDimensions.y())};
};

#endif
