/**
 * @file arythmatik.cpp
 * @author Adam Wonak (https://github.com/awonak)
 * @brief Library for building custom scripts for Modulove modules.
 * @version 0.2
 * @date 2023-09-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "arythmatik.h"

using namespace modulove;

void Arythmatik::Init() {
    InitInputs();
    InitOutputs();
    InitDisplay();

    // CLOCK LED (DIGITAL)
    pinMode(CLOCK_LED, OUTPUT);
}

void Arythmatik::InitDisplay() {
    // OLED Display configuration.
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
#ifdef ROTATE_PANEL
    display.setRotation(2);  // 180 degree rotation for upside-down use
#endif
    display.display();
}

void Arythmatik::InitInputs() {
    clk.Init(CLK_PIN);
    rst.Init(RST_PIN);
}

void Arythmatik::InitOutputs() {
    // Initialize each of the outputs with it's GPIO pins and probability.
    outputs[0].Init(OUT_CH1, LED_CH1);
    outputs[1].Init(OUT_CH2, LED_CH2);
    outputs[2].Init(OUT_CH3, LED_CH3);
    outputs[3].Init(OUT_CH4, LED_CH4);
    outputs[4].Init(OUT_CH5, LED_CH5);
    outputs[5].Init(OUT_CH6, LED_CH6);
}

void Arythmatik::ProcessInputs() {
    clk.Process();
    rst.Process();

    // Clock In LED indicator mirrors the clock input.
    if (clk.State() == DigitalInput::STATE_RISING) {
        digitalWrite(CLOCK_LED, HIGH);
    } else if (clk.State() == DigitalInput::STATE_FALLING) {
        digitalWrite(CLOCK_LED, LOW);
    }
}
