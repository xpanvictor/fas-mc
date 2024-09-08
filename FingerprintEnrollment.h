#ifndef FINGERPRINT_ENROLLMENT_H
#define FINGERPRINT_ENROLLMENT_H

#include <Adafruit_Fingerprint.h>
#include "keyboard.h"
// #include "ServerCommunication.h"

extern Adafruit_Fingerprint finger;

String generateFingerprintID() {
 
  Serial.print("Enrolling finger");

  // if (finger.getImage() != FINGERPRINT_OK) return;
  // if (finger.image2Tz(1) != FINGERPRINT_OK) return;
  // if (finger.createModel() != FINGERPRINT_OK) return;

  Serial.println("Fingerprint enrolled!");

  return String(finger.fingerID);
}

void enrollFingerprint() {
  Serial.println("Enroll mode entered");

  Serial.println("Enter matric number:");
  char* matricNo = getInput();

  Serial.print("Enrolling ID #"); Serial.println(matricNo);

  // Send data to the server
  String fingerprintID = generateFingerprintID();
  // String data = "studentId=<TODO>" + "&fingerprint=" + String(fingerprintID);
  // Serial.print(data); 
  Serial.println("simulated server");
  // sendToServer(data);
}

#endif
