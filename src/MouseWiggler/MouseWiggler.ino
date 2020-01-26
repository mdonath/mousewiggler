//////////////////////////////////
// Board: Arduino/Genuino Micro
//////////////////////////////////

#include <Mouse.h>
#include <Keyboard.h>

////////////////////////////////////
// References:
// - https://www.arduino.cc/en/Reference/KeyboardModifiers
////////////////////////////////////

const int HEARTBEAT_MS = 1000;  // millis

const int WIGGLE_AMPLITUDE = 1; // pixels
const int WIGGLE_EVERY = 0;    // seconds

const int SCROLL_AMPLITUDE = 0; // pixels
const int SCROLL_EVERY = 0;    // seconds

const int SWITCHTAB_EVERY = 60; // seconds

const int BLINK_TIME = 50;      // milliseconds
const int LED_PIN = LED_BUILTIN;

//////////////////////////////////
int heartbeatCounter = 0;
int wiggleDirection = WIGGLE_AMPLITUDE;
int scrollDirection = SCROLL_AMPLITUDE;
//////////////////////////////////

/**
     Setup as mouse.
*/
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Mouse.begin();
  Keyboard.begin();
}

/**
     Loop every DELAYTIME ms.
*/
void loop() {
  heartbeatCounter++;

  // Change the horizontal direction of the mouse
  if (WIGGLE_EVERY != 0 && heartbeatCounter % WIGGLE_EVERY == 0) {
    wiggleDirection *= -1;
    Mouse.move(wiggleDirection, 0, 0);
    // Blink the LED only when BLINK_TIME is larger than zero
    if (BLINK_TIME > 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(BLINK_TIME);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  // Scroll page to top or bottom
  if (SCROLL_EVERY && heartbeatCounter % SCROLL_EVERY == 0) {
    scrollDirection *= -1;
    // Keyboard.press(KEY_CONTROL);
    if (scrollDirection > 0) {
      Keyboard.press(KEY_END);
    } else {
      Keyboard.press(KEY_HOME);
    }
    Keyboard.releaseAll();
  }

  // Send Ctrl-Tab to switch to next browser tab
  if (SWITCHTAB_EVERY != 0 && heartbeatCounter % SWITCHTAB_EVERY == 0) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
    if (BLINK_TIME > 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(BLINK_TIME);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  // Wait a few seconds
  delay(HEARTBEAT_MS);
}
