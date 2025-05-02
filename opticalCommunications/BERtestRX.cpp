#include <Arduino.h>

const int rxPin = 16;
const int txPin = 17;
const int expectedMax = 256;
const unsigned long baudRate = 3000000;  // Set this to match transmitter

int expectedValue = 0;
int numErrors = 0;
int numReceived = 0;

unsigned long lastReportTime = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial2.begin(baudRate, SERIAL_8N1, rxPin, txPin);
  Serial.printf("Listening at baud rate = %lu\n", baudRate);
  lastReportTime = millis();
}

void loop() {
  while (Serial2.available()) {
    int received = Serial2.read();
    if (received != expectedValue) {
      numErrors++;
    }
    expectedValue = (expectedValue + 1) % expectedMax;
    numReceived++;
  }

  if (millis() - lastReportTime >= 1000) {
    float ber = (numReceived == 0) ? 0.0 : (100.0 * numErrors / numReceived);
    Serial.println();
    Serial.println("=======================================");
    Serial.printf("Baud rate       : %lu\n", baudRate);
    Serial.printf("Dropped packets : %d\n", numErrors);
    Serial.printf("BER %%           : %.2f\n", ber);
    Serial.println("=======================================");


    // Reset for next second
    lastReportTime = millis();
    numErrors = 0;
    numReceived = 0;
    expectedValue = 0;
  }
}
