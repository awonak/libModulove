#ifndef SYNCLFO_H
#define SYNCLFO_H

#include <Arduino.h>

// Oled setting
#include "analog_input.h"
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

    AnalogInput p1;
    AnalogInput p2;
    AnalogInput p3;
    AnalogInput p4;
    AnalogInput p[P_COUNT] = {p1, p2, p3, p4};

    DigitalInput gate;
    DigitalInput trig;
    DigitalOutput output;

   private:
    void InitInputs();
    void InitOutputs();
};
}  // namespace modulove

#endif
