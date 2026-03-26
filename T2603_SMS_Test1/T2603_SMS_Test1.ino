#include <SoftwareSerial.h>

SoftwareSerial Serial1(7, 8);  // RX, TX

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  delay(1000);
  Serial.println("Initializing Serial1C...");

  sendCommand("AT");
  sendCommand("AT+CMGF=1");  // SMS text mode
  sendCommand("AT+CSCS=\"GSM\""); // Character set

  // Replace with your phone number
  sendSMS("+1234567890", "Hello from Serial1C!");
}

void loop() {
}

void sendSMS(const char* number, const char* message) {
  Serial.println("Sending SMS...");

  Serial1.print("AT+CMGS=\"");
  Serial1.print(number);
  Serial1.println("\"");
  delay(500);

  Serial1.print(message);
  delay(300);

  Serial1.write(26); // CTRL+Z to send
  Serial.println("SMS sent.");
}

void sendCommand(const char* cmd) {
  Serial1.println(cmd);
  delay(500);
  while (Serial1.available()) Serial.write(Serial1.read());
}