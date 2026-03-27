#include <Arduino.h>
/*
 * ESP32 Manual UART Bridge
 * Change ROUTER_BAUD to try different speeds
 */

// --- CONFIGURATION ---
#define ROUTER_BAUD 115200  // <-- CHANGE THIS if needed (Try 115200, 57600, 38400, 9600)
#define PC_BAUD 115200

#define RX2_PIN 16          // Connected to Router TX
#define TX2_PIN 17          // Connected to Router RX
// ---------------------

void setup() {
  //Initialize USB Serial to PC
  Serial.begin(PC_BAUD);
  delay(1000);
  
  Serial.println("\n------------------------------------");
  Serial.print("BRIDGE ACTIVE | Baud: ");
  Serial.println(ROUTER_BAUD);
  Serial.println("Ensure Router TX -> Pin 16, RX -> Pin 17");
  Serial.println("------------------------------------\n");

  // Initialize Hardware Serial 2 to Router
  // SERIAL_8N1 is the standard (8 bits, No parity, 1 stop bit)
  Serial2.begin(ROUTER_BAUD, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

void loop() {
  // Read from Router, send to PC
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  
  // Read from PC, send to Router
  if (Serial.available()) {
    char c = Serial.read();
    Serial2.write(c);
  }
}