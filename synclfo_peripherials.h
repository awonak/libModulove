/**
 * @file synclfo_peripherials.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Arduino pin definitions for the Modulove SyncLFO module.
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SYNCLFO_PERIPHERIALS_H
#define SYNCLFO_PERIPHERIALS_H

namespace modulove {
namespace synclfo {

// GPIO Pin mapping.
const uint8_t P1 = 0;  // Knob 1
const uint8_t P2 = 1;  // Knob 2
const uint8_t P3 = 3;  // Knob 3
const uint8_t P4 = 5;  // Knob 4

const uint8_t P_COUNT = 4;  // Number of knobs.
const uint8_t P[P_COUNT] = {P1, P2, P3, P4};  // Array of knob GPIO pin identifiers.

const uint8_t GATE_IN = 3;  // Digital Input
const uint8_t CV_OUT = 10;  // CV Output for current step

}  // namespace synclfo
}  // namespace modulove

#endif
