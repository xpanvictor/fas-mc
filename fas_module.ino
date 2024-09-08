
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

// #include "SetupFingerprint.h"
// #include "WifiSetup.h"
// #include "FingerprintVerification.h"
#include "FingerprintEnrollment.h"
// #include "ServerCommunication.h"
#include "ClassMode.h"
#include "keyboard.h"
#include "Screen.h"

void setup() {
  Serial.begin(9600);
  Serial.println("FAS module init");
  // setupWiFi();
  // setupFingerprintSensor();
}

void loop() {
  printToScreen("Select Mode: 1 for ENROLL, 2 for START CLASS");
  char key = waitForKeyPress(); // Get input from the 4x4 keypad
  
  int currentMode = (int)key;
  switch(key) {
    case '1':
      enrollFingerprint();
      break;
    case '2': 
      classMode();
      break;
    default:
      printToScreen("Invalid mode");
  }
}

