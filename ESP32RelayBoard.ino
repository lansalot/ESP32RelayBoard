int latchPin = 12; // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 13; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 14;  // Data pin of 74HC595 is connected to Digital pin 4
int oePin = 5;     // oePin - not using this

uint16_t relayState = 0; // Stores the current state of all 16 relays

void setup()
{
      // Set all the pins of 74HC595 as OUTPUT
      pinMode(latchPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(oePin, OUTPUT);
      
      // Initialize all relays to OFF
      updateRelays();
}

// Function to set relay state (relay number 1-16, state true=ON/false=OFF)
void setRelay(int relayNum, bool state)
{
      if (relayNum < 1 || relayNum > 16) return; // Validate relay number
      
      int bitPos = relayNum - 1; // Convert to 0-based index
      
      if (state) {
            relayState |= (1 << bitPos);  // Turn relay ON
      } else {
            relayState &= ~(1 << bitPos); // Turn relay OFF
      }
      
      updateRelays();
}

// Function to update the shift registers with current relay state
void updateRelays()
{
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, (relayState >> 8));
      shiftOut(dataPin, clockPin, MSBFIRST, relayState);
      digitalWrite(latchPin, HIGH);
}

void loop()
{
      // Example: Turn on relays one by one, then turn them all off
      for (int i = 1; i <= 16; i++) {
            setRelay(i, true);  // Turn relay ON
            delay(100);
      }
      
      for (int i = 1; i <= 16; i++) {
            setRelay(i, false);  // Turn relay OFF
            delay(100);
      }
      
      // You can also control individual relays:
      // setRelay(5, true);   // Turn relay 5 ON
      // setRelay(12, false); // Turn relay 12 OFF
}