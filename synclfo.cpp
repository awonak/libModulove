/**
 * @file synclfo.cpp
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Library for building custom scripts for the Modulove SyncLFO.
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "synclfo.h"

using namespace modulove;
using namespace synclfo;

void SyncLFO::Init() {
    InitInputs();
    InitOutputs();
}

void SyncLFO::InitInputs() {
    gate.Init(GATE_IN);
    trig.Init(GATE_IN);

    for (int i = 0; i < P_COUNT; i++) {
        knobs[i].Init(KNOB_PINS[i]);
    }

    if (config.Synchronizer) {
        b1.Init(B1_PIN, LED1_PIN);
        b2.Init(B2_PIN);
    }
}

void SyncLFO::InitOutputs() {
    output.Init(CV_OUT);

    // Register setting for high frequency PWM.
    TCCR1A = 0b00100001;
    TCCR1B = 0b00100001;
}

void SyncLFO::ProcessInputs() {
    gate.Process();
    trig.Process();

    for (int i = 0; i < P_COUNT; i++) {
        knobs[i].Process();
    }

    if (config.Synchronizer) {
        b1.Process();
        b2.Process();
    }
}
