/**
 * @file button.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Class for interacting with trigger / gate inputs.
 * @version 0.1
 * @date 2024-06-28
 *
 * Provide methods to convey curent state (HIGH / LOW) and change in state (disengaged, engageing, engaged, disengaging).
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

namespace modulove {

const uint8_t DEBOUNCE_MS = 10;

class Button {
   public:
    /// @brief Enum constants for active change in button state.
    enum ButtonChange {
        CHANGE_UNCHANGED,
        CHANGE_PRESSED,
        CHANGE_RELEASED,
    };

    Button() {}
    ~Button() {}

    /**
     * @brief Initializes a CV Input object.
     *
     * @param pin gpio pin for the cv output.
     */
    void Init(uint8_t pin) {
        pinMode(pin, INPUT_PULLUP);
        pin_ = pin;
    }

    /**
     * @brief Initializes an Button paired with an LED.
     *
     * @param pin gpio pin for the button input
     * @param led_pin gpio pin for the LED
     */
    void Init(uint8_t pin, uint8_t led_pin) {
        pinMode(led_pin, OUTPUT);
        led_pin_ = led_pin; 
#define LED_PIN_DEFINED
        Init(pin);
    }

    /**
     * @brief Read the state of the cv input.
     *
     */
    void Process() {
        old_read_ = read_;
        read_ = digitalRead(pin_);

        bool debounced = (millis() - last_press_) > DEBOUNCE_MS;
        bool pressed = read_ == 0 && old_read_ == 1 && debounced;
        bool released = read_ == 1 && old_read_ == 0 && debounced;
        // Update variables for next loop
        last_press_ = (pressed || released) ? millis(): last_press_;

        // Determine current clock input state.
        change_ = CHANGE_UNCHANGED;
        if (pressed) {
            change_ = CHANGE_PRESSED;
            on_ = true;
        } else if (released) {
            change_ = CHANGE_RELEASED;
            on_ = false;
        }
        #ifdef LED_PIN_DEFINED
        // Change LED state
        digitalWrite(led_pin_, on_);
        #endif
    }

    /**
     * @brief Get the state change for the button.
     *
     * @return ButtonChange
     */
    inline ButtonChange Change() { return change_; }

    /**
     * @brief Current cv state represented as a bool.
     *
     * @return true if cv signal is high
     * @return false if cv signal is low
     */
    inline bool On() { return on_; }

   private:
    uint8_t pin_;
    uint8_t led_pin_;
    uint8_t read_;
    uint8_t old_read_;
    unsigned long last_press_;
    ButtonChange change_;
    bool on_;
};

}  // namespace modulove

#endif
