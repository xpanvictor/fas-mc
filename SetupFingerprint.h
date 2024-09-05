
#ifndef SETUP_FINGERPRINT_H
#define SETUP_FINGERPRINT_H

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "ServerCommunication.h"

extern Adafruit_Fingerprint finger;
extern SoftwareSerial fingerSerial;

// Define the setupFingerprintSensor function
void setupFingerprintSensor() {
  fingerSerial.begin(57600);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);  // Stop the program if the sensor is not found
  }
}

#endif
