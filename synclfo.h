#ifndef SYNCLFO_H
#define SYNCLFO_H

#include <Arduino.h>

// Oled setting
#include "analog_input.h"
#include "analog_output.h"
#include "button.h"
#include "synclfo_config.h"
#include "synclfo_peripherials.h"
#include "digital_input.h"
#include "digital_output.h"

namespace modulove {

/// @brief Hardware abstraction wrapper for SyncLFO module.
class SyncLFO {
   public:
    /// @brief Constructor
    SyncLFO(){}

    /// @brief Deconstructor
    ~SyncLFO() {}

    /// @brief Initializes the Arduino, and SyncLFO hardware.
    void Init();

    /// @brief Read the state of the CLK and RST inputs.
    void ProcessInputs();


    // Module configuration storage struct.
    synclfo::Config config;

    AnalogInput p1;
    AnalogInput p2;
    AnalogInput p3;
    AnalogInput p4;
    AnalogInput *knobs[synclfo::P_COUNT];

    DigitalInput gate;
    DigitalInput trig;
    AnalogOutput output;

    // Synchronizer hardware
    Button b1;
    Button b2;

   private:
    void InitInputs();
    void InitOutputs();
};
}  // namespace modulove

#endif
