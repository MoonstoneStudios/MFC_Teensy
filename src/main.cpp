#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include "ErrorCodes.h"

// https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/examples/sevenseg/sevenseg.ino
Adafruit_7segment display   { };
IntervalTimer blinkTimer    { };
volatile bool ledOn         { false };
uint32_t loops              { 0 };
bool doneLooping            { false };

/// @brief Store the error codes that occur.
int errors { RSX_NO_ERRROR };

// Foreward declaration
void blink();

void setup() {
  blinkTimer.begin(blink, 1000000); // One second in microseconds.

  SerialUSB.begin(9600);

  // Wait for serial.
  while (!SerialUSB) delay(10);

  // Start the I2C connection to the display.
  // Two 2k ohm pullup-resistors are used for I2C here
  // because Teensy 4.1 has 3.3V logic levels.
  // If returns false, there was an error.  
  if (!display.begin(0x70, &Wire)) {
    SerialUSB.println("Could not open i2c!");
    while(1) {
      delay(10);
    }
  }

  // Refresh
  display.println(0);
  display.writeDisplay();
}

void loop() {
  SerialUSB.print("Doing some arbitrary work....");
  SerialUSB.println(loops);
  loops++;

  // do some unblocking waiting 
  if (loops >= 10'000 && !doneLooping) {
    loops = 0;
    doneLooping = true;
  }

  // Pertend like an error actually happened. 
  if (doneLooping) {
    SerialUSB.println("Lets try and read from the LIDAR sensor. It uses USB serial.");

    Serial1.begin(9600);
    while (!Serial1) delay(10);

    // Get the important 'LIDAR is connected' byte!
    int alive = Serial1.read();

    // No serial connected :(
    if (alive < 0) {
      errors |= RSX_LIDAR_USB_NOT_CONN;
    }
  }
  
  // Write status.
  display.println(errors, HEX);
  // display the new status
  display.writeDisplay(); 

  if (doneLooping) {
    while(1) delay(10);
  }
}

/// @brief Handle the 1 second blink timer.
void blink() {
  ledOn = !ledOn;
  digitalWrite(LED_BUILTIN, ledOn);
}