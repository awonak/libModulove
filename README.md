# Modulove Hardware Abstraction Library

This package provides a library for creating A-RYTH-MATIK scripts.

There are two ways to install. Include the library directly in your script
repo as a git submodule, or download the latest release zip and extract the
library into your `~/Arduino/libraries` folder.

**Include the library as a git submodule to use in your scripts.**

```bash
git submodule add https://github.com/awonak/libmodulove.git path/to/your/script
```

**Download the latest release.**

[TODO]

## Example usage

```cpp
#include "modulove_arythmatik.h"

using namespace modulove;
using namespace arythmatik;

// Declare A-RYTH-MATIK hardware variable.
Arythmatik hw;

byte counter = 0;

void setup() {
    // Initialize the A-RYTH-MATIK peripherials.
    hw.Init();
}

void loop() {
    // Read inputs to determine state.
    hw.ProcessInputs();

    // Advance the counter
    if (hw.Clk.State() == DigitalInput::STATE_RISING) {
        counter = ++counter % OUTPUT_COUNT;
    }

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
```

### Third-party Arduino Libraries

* [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [Simple Rotary](https://github.com/mprograms/SimpleRotary/tree/master)
