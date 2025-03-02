# Modulove Hardware Abstraction Library

This package provides a library for creating scripts for the Modulove [A-RYTH-MATIK](https://modulove.io/arythmatik/) eurorack module.

Full Doxyen generated documentation of the library can be found here: [https://awonak.github.io/libModulove/](https://awonak.github.io/libModulove/).

## Installation instructions

**Option 1: Arduino CLI**

The recommended way to install the library is to use the Arduino CLI to download the library code directly from GitHub.

```
$ arduino-cli config init
$ arduino-cli config set library.enable_unsafe_install true
$ arduino-cli lib install --git-url https://github.com/awonak/libModulove.git 
```

**Option 2: Clone and symlink the repo**
```
$ git clone https://github.com/awonak/libModulove.git
$ ln -s `pwd`/libmodulove ~/Arduino/libraries  
```

**Option 3: Include the library as a git submodule to use in your scripts.**

In order to include the library source code directly in your repo as a git
submodule, you must follow the Arduino Sketch specifications and place the
code in the location `<sketch>/src/<library>`. This is documented in the
[src subfolder](https://arduino.github.io/arduino-cli/0.34/sketch-specification/#src-subfolder)
section of the Arduino Sketch Specification.

```bash
git submodule add https://github.com/awonak/libmodulove.git <sketch>/src/libmodulove
```

## Example usage for A-RYTH-MATIK

```cpp
#include "src/libmodulove/arythmatik.h"

using namespace modulove;
using namespace arythmatik;

// Declare A-RYTH-MATIK hardware variable.
Arythmatik hw;

// Since counter is modified in the CLK/RST handler, it should be volatile.
volatile int counter;

void setup() {
    // Inside the setup, set config values prior to calling hw.Init().
    #ifdef ROTATE_PANEL
        hw.config.RotatePanel = true;
    #endif
    #ifdef ENCODER_REVERSED
        hw.config.ReverseEncoder = true;
    #endif

    // Set up encoder parameters
    hw.eb.setEncoderHandler(UpdateRotate);
    hw.eb.setClickHandler(UpdatePress);

    // Attach CLK & RST pin change handlers.
    hw.AttachClockHandler(HandleClockPinChange);
    hw.AttachResetHandler(HandleResetPinChange);

    // Initialize the A-RYTH-MATIK peripherials.
    hw.Init();
}

void loop() {
    // Read cv inputs and process encoder state to determine state for this loop.
    hw.ProcessInputs();

    // Activate the current counter output.
    for (int i = 0; i < OUTPUT_COUNT; i++) {
        (i == counter)
            ? hw.outputs[i].High()
            : hw.outputs[i].Low();
    }

    // Display the current counter step on the OLED.
    hw.display.clearDisplay();
    hw.display.setCursor(SCREEN_HEIGHT/2, 0);
    hw.display.println("Counter: " + String(counter));
    hw.display.display();
}

void HandleClockPinChange() {
    // Advance the counter on CLK input
    if (hw.clk.Read() == HIGH) {
        counter = ++counter % OUTPUT_COUNT;
    }
}

void HandleResetPinChange() {
    if (hw.rst.Read() == HIGH) {
        counter = 0;
    }
}

void UpdateRotate(EncoderButton &eb) {
    // Read the configured encoder direction (according to hw.config.ReverseEncoder setting).
    Direction dir = hw.EncoderDirection();
    // Read the number of rotation clicks since the last encoder handler event.
    int rotate_count = eb.increment();

    counter = (dir == DIRECTION_INCREMENT) 
        ? min(counter + rotate_count, OUTPUT_COUNT)
        : max(counter - rotate_count, 0);
}

void UpdatePress(EncoderButton &eb) {
    // Reset the counter to zero.
    counter = 0;
}
```

## Example usage for SyncLFO

```cpp
#include "src/libmodulove/arythmatik.h"

using namespace modulove;
using namespace synclfo;

// Declare A-RYTH-MATIK hardware variable.
SyncLFO hw;

byte step = 0;

void setup() {
    // Inside the setup, set config values prior to calling hw.Init().
    #ifdef SYNCHRONIZER
        hw.config.Synchronizer = true;
    #endif

    // Initialize the SyncLFO peripherials.
    hw.Init();
}

void loop() {
    // Read cv inputs and process button state to determine state for this loop.
    hw.ProcessInputs();

    // Read cv inputs to determine state for this loop.
    hw.ProcessInputs();

    bool advance = hw.trig.State() == DigitalInput::STATE_RISING;
    if (hw.config.Synchronizer) {
        advance |= hw.b1.Change() == Button::CHANGE_PRESSED;
    }

    // Detect if new trigger received and advance step.
    if (advance) {
        step = (step + 1) % synclfo::P_COUNT;
    }

    // Write current step CV output.
    byte val = map(hw.knobs[step]->Read(), 0, MAX_INPUT, 0, MAX_OUTPUT);
    hw.output.Update(val);
}
```

### Third-party Arduino Libraries

* [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [EncoderButton](https://github.com/Stutchbury/EncoderButton)
