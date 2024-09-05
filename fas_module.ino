
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

#include "SetupFingerprint.h"
#include "WifiSetup.h"
#include "FingerprintVerification.h"
#include "FingerprintEnrollment.h"
#include "ServerCommunication.h"

void setup() {
  Serial.println("FAS module init");
  Serial.begin(9600);
  setupWiFi();
  setupFingerprintSensor();
}

void loop() {
  // Check if enrollment button is pressed
  if (digitalRead(4) == HIGH) {
    enrollFingerprint();
  }
  // Check if verification button is pressed
  else if (digitalRead(5) == HIGH) {
    verifyFingerprint();
  }
}

