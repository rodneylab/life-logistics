#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H

/*! \file src/constants.h
 * \brief Declarations for game constants used throughout the project
 */

#include "vector2d.h"

#include <string_view>

namespace constants
{
inline constexpr int kWindowWidth{800U};
inline constexpr int kWindowHeight{450U};

inline const std::string_view kWindowTitle{"Life Logistics"};

inline constexpr int kTargetFramerate{240};
inline const Vector2D kTileDimensions{16, 16};
inline constexpr int kLevelWidth{64};
inline constexpr int kLevelHeight{29};

inline constexpr float kPlayerSpeed{6.F};
} // namespace constants

#endif
