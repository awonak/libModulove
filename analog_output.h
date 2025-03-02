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

const int MAX_OUTPUT = (1 << 8) - 1;  // Max 8 bit output resolution.
const int MAX_OUTPUT_10BIT = (1 << 10) - 1;  // Max 10 bit output resolution.

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
     * @brief Set the output pin to the given 8 bit value.
     *
     * @param val Arduino analog value between 0 and 255 (0..10v).
     */
    inline void Update(int val) {
        update((val <= MAX_OUTPUT) ? val : MAX_OUTPUT);
    }

    /**
     * @brief Set the output pin to the given 10 bit value.
     *
     * @param val Arduino analog value between 0 and 1024 (0..10v).
     */
    inline void Update10bit(int val) {
        val = val <= MAX_OUTPUT_10BIT ? val : MAX_OUTPUT_10BIT;
        val = map(val, 0, MAX_OUTPUT_10BIT, 0, MAX_OUTPUT);
        update(val);
    }

    /// @brief Sets the cv output HIGH to about 10v.
    inline void High() { update(MAX_OUTPUT); }

    /// @brief Sets the cv output LOW to 0v.
    inline void Low() { update(0); }

    /**
     * @brief Return an integer value between 0 and 1023 (0..10v) representing the current value of the output.
     *
     * @return integer value of cv from 0 to 1023.
     */
    inline uint16_t GetValue() { return cv_; }

   private:
    uint8_t cv_pin_;
    uint8_t led_pin_;
    uint8_t cv_;

    void update(uint16_t val) {
        cv_ = val;
        analogWrite(cv_pin_, cv_);
        #ifdef LED_PIN_DEFINED
        analogWrite(led_pin_, cv_);
        #endif
    }
};

}  // namespace modulove

#endif
