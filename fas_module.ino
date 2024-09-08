
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

// #include "SetupFingerprint.h"
// #include "WifiSetup.h"
// #include "FingerprintVerification.h"
#include "FingerprintEnrollment.h"
// #include "ServerCommunication.h"

#include "keyboard.h"

void setup() {
  Serial.begin(9600);
  Serial.println("FAS module init");
  // setupWiFi();
  // setupFingerprintSensor();
}
  
// void loop() {
//   char* input = getInput();
//   Serial.print("Input: ");
//   Serial.println(input);
//   delay(2000);
//   // User flow


//   // // Check if enrollment button is pressed
//   // if (digitalRead(4) == HIGH) {
//   //   enrollFingerprint();
//   // }
//   // // Check if verification button is pressed
//   // else if (digitalRead(5) == HIGH) {
//   //   verifyFingerprint();
//   // }
//   // Clean up ops
//   free(input);
// }

void loop() {
  Serial.println("Select Mode: 1 for ENROLL, 2 for START CLASS");
  char key = waitForKeyPress(); // Get input from the 4x4 keypad
  
  int currentMode = (int)key;
  switch(key) {
    case '1':
      enrollFingerprint();
      break;
    case '2': 
      Serial.println("Class start mode initiated");
      break;
    default:
      Serial.println("Invalid mode");
  }
}

