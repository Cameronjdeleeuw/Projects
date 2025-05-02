#include <Arduino.h>

const int txPin = 17;
const unsigned long baudRate = 3000000;  // Match with receiver

void setup() {
  Serial2.begin(baudRate, SERIAL_8N1, -1, txPin);  // TX only
}

void loop() {
  for (int i = 0; i < 256; i++) {
    Serial2.write(i);  // 8-bit value
  }
}
