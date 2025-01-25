#ifndef ARYTHMATIK_H
#define ARYTHMATIK_H

#include <Arduino.h>

// Oled setting
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <EncoderButton.h>
#include <Wire.h>

#include "arythmatik_config.h"
#include "arythmatik_peripherials.h"
#include "digital_input.h"
#include "digital_output.h"
#include "encoder_dir.h"

namespace modulove {

/// @brief Hardware abstraction wrapper for A-RYTH-MATIK module.
class Arythmatik {
   public:
    /// @brief Constructor
    Arythmatik()
        : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
          eb(ENCODER_PIN1, ENCODER_PIN2, ENCODER_SW_PIN) {}

    /// @brief Deconstructor
    ~Arythmatik() {}

    // Module configuration storage struct.
    arythmatik::Config config;

    /// @brief Initializes the Arduino, and A-RYTH-MATIK hardware.
    void Init();

    /// @brief Read the state of the CLK and RST inputs.
    void ProcessInputs();

    /// @brief Parse the configured EncoderButton increment direction.
    /// @return Direction of turn or unchanged.
    arythmatik::Direction EncoderDirection();

    Adafruit_SSD1306 display;                         ///< OLED display object.
    EncoderButton eb;                                 ///< EncoderButton object.
    DigitalOutput outputs[arythmatik::OUTPUT_COUNT];  ///< An array containing
                                                      ///< each Output object.
    DigitalInput clk;  ///< CLK Digital Input object.
    DigitalInput rst;  ///< RST Digital Input object.

   private:
    void InitDisplay();
    void InitInputs();
    void InitOutputs();
};
}  // namespace modulove

#endif
