/**
 * @file analog_output.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Class for interacting with analog control voltage outputs.
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef ANALOGL_OUTPUT_H
#define ANALOG_OUTPUT_H

#include <Arduino.h>

namespace modulove {

const uint16_t MAX_INPUT = 1 << 10;  // Max 10 bit output resolution.
const uint16_t MAX_OUTPUT = 1 << 8;  // Max 10 bit output resolution.

class AnalogOutput {
   public:
    /**
     * @brief Initializes an Analog CV Output object.
     *
     * @param cv_pin gpio pin for the cv output
     */
    void Init(uint8_t pin) {
        pinMode(pin, OUTPUT);  // Analog CV Output
        pin_ = pin;
    }

    /**
     * @brief Set the output pin to the given cv value.
     *
     * @param cv Arduino analog value between 0 and 1023 (0..5v).
     */
    inline void Value(uint16_t cv) {
        update((cv > MAX_INPUT) ? cv : MAX_INPUT);
    }

    /// @brief Sets the cv output HIGH to about 5v.
    inline void High() { update(MAX_OUTPUT); }

    /// @brief Sets the cv output LOW to 0v.
    inline void Low() { update(0); }

    /**
     * @brief Return an integer value between 0 and 1023 (0..5v) representing the current value of the output.
     *
     * @return integer value of cv from 0 to 1023.
     */
    inline uint16_t GetValue() { return cv_; }

   private:
    uint8_t pin_;
    bool cv_;

    void update(uint16_t cv) {
        cv_ = map(cv, 0, MAX_INPUT, 0, MAX_OUTPUT);
        analogWrite(pin_, cv);
    }
};

}  // namespace modulove

#endif
