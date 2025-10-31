#include "ESP32RelayClass.ino"

// Create relay board instance with pin configuration
// Pin assignments: latchPin=12, clockPin=13, dataPin=14, oePin=5
RelayBoard relayBoard(12, 13, 14, 5);

void setup()
{
      // Initialize the relay board
      relayBoard.begin();
}

void loop()
{
      // Turn on relays one by one (cascading effect)
      for (int i = 1; i <= 16; i++) {
            relayBoard.setRelay(i, true);
            delay(250);
      }
      
      // Turn off relays one by one
      for (int i = 1; i <= 16; i++) {
            relayBoard.setRelay(i, false);
            delay(250);
      }
}
