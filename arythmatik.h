#ifndef ARYTHMATIK_H
#define ARYTHMATIK_H

#include <Arduino.h>

// Oled setting
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <Wire.h>

// Encoder & button
#include <SimpleRotary.h>

#include "arythmatik_peripherials.h"
#include "digital_input.h"
#include "digital_output.h"

namespace modulove {

/// @brief Hardware abstraction wrapper for A-RYTH-MATIK module.
class Arythmatik {
   public:
    /// @brief Constructor
    Arythmatik() : 
      encoder(ENCODER_PIN1, ENCODER_PIN2, ENCODER_SW_PIN),
      display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

    /// @brief Deconstructor
    ~Arythmatik() {}

    /// @brief Initializes the Arduino, and A-RYTH-MATIK hardware.
    void Init();

    /// @brief Read the state of the CLK and RST inputs.
    void ProcessInputs();

    Adafruit_SSD1306 display;                         ///< OLED display object.
    SimpleRotary encoder;                             ///< Rotary encoder object.
    DigitalOutput outputs[arythmatik::OUTPUT_COUNT];  ///< An array containing each Output object.
    DigitalInput Clk;                                 ///< CLK Digital Input object.
    DigitalInput Rst;                                 ///< RST Digital Input object.

   private:
    void InitDisplay();
    void InitInputs();
    void InitOutputs();
};
}  // namespace modulove

#endif
