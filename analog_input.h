/**
 * @file analog_input.h
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Class for interacting with analog inputs.
 * @version 0.1
 * @date 2024-06-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include <Arduino.h>

namespace modulove {

class AnalogInput {
   public:
    AnalogInput() {}
    ~AnalogInput() {}

    /**
    * @brief Initializes a analog input object.
    * 
    * @param pin gpio pin for the analog input.
    */
    void Init(uint8_t pin) {
        pinMode(pin, INPUT);
        pin_ = pin;
    }

    /**
     * @brief Read the value of the analog input.
     * 
     */
    void Process() {
        old_read_ = read_;
        read_ = analogRead(pin_);
    }

    /**
     * @brief Get the current value of the analog input.
     * 
     * @return InputState 
     */
    inline uint16_t Read() { return read_; }

   private:
    uint8_t pin_;
    uint8_t read_;
    uint8_t old_read_;
};

}  // namespace modulove

#endif
