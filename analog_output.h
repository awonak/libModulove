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
const uint16_t MAX_OUTPUT = 1 << 8;  // Max 8 bit output resolution.

class AnalogOutput {
   public:
    /**
     * @brief Initializes an Analog CV Output object.
     *
     * @param pin gpio pin for the cv output
     */
    void Init(uint8_t pin) {
        pinMode(pin, OUTPUT);  // Analog CV Output
        cv_pin_ = pin;
    }

    /**
     * @brief Initializes an LED & CV Output paired object.
     * 
     * @param cv_pin gpio pin for the cv output
     * @param led_pin gpio pin for the LED
     */
    void Init(uint8_t cv_pin, uint8_t led_pin) {
        pinMode(led_pin, OUTPUT);  // LED
        led_pin_ = led_pin;
        #define LED_PIN_DEFINED
        Init(cv_pin);
    }

    /**
     * @brief Set the output pin to the given cv value.
     *
     * @param val Arduino analog value between 0 and 1023 (0..5v).
     */
    inline void Update(uint16_t val) {
        update((val < MAX_INPUT) ? val : MAX_INPUT);
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
    uint8_t cv_pin_;
    uint8_t led_pin_;
    uint8_t cv_;

    void update(uint16_t val) {
        cv_ = map(val, 0, MAX_INPUT, 0, MAX_OUTPUT);
        analogWrite(cv_pin_, cv_);
        #ifdef LED_PIN_DEFINED
        analogWrite(led_pin_, cv_);
        #endif
    }
};

}  // namespace modulove

#endif
