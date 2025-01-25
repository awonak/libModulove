/**
 * @file encoder_dir.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Class for interacting with encoder push buttons.
 * @version 0.1
 * @date 2023-09-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef ENCODER_DIR_H
#define ENCODER_DIR_H

namespace modulove {
namespace arythmatik {

/// @brief Enum constants for encoder rotation increment/decrement state.
enum Direction {
    DIRECTION_UNCHANGED,
    DIRECTION_INCREMENT,
    DIRECTION_DECREMENT,
};

inline Direction rotate_(int dir) {
    switch (dir) {
        case 1:
            return DIRECTION_INCREMENT;
        case -1:
            return DIRECTION_DECREMENT;
        default:
            return DIRECTION_UNCHANGED;
    }
}

inline Direction rotate_reversed_(int dir) {
    switch (dir) {
        case 1:
            return DIRECTION_DECREMENT;
        case -1:
            return DIRECTION_INCREMENT;
        default:
            return DIRECTION_UNCHANGED;
    }
}

/// @brief Parse EncoderButton increment direction.
/// @return Direction of turn or unchanged.
inline Direction Rotate(int dir, bool reversed) {
    int _dir = dir > 0 ? 1 : -1;
    return (reversed)
                ? rotate_reversed_(_dir)
                : rotate_(_dir);
}

}  // namespace arythmatik
}  // namespace modulove

#endif