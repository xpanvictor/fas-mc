#ifndef FINGERPRINT_ENROLLMENT_H
#define FINGERPRINT_ENROLLMENT_H

#include <Adafruit_Fingerprint.h>
#include "Screen.h"
#include "keyboard.h"
// #include "ServerCommunication.h"

extern Adafruit_Fingerprint finger;

String generateFingerprintID() {
 
  printToScreen("Enrolling finger");

  // if (finger.getImage() != FINGERPRINT_OK) return;
  // if (finger.image2Tz(1) != FINGERPRINT_OK) return;
  // if (finger.createModel() != FINGERPRINT_OK) return;

  printToScreen("Fingerprint enrolled!");

  return String(finger.fingerID);
}

void enrollFingerprint() {
  printToScreen("Enroll mode entered");

  printToScreen("Enter matric number:");
  char* matricNo = getInput();

  printToScreen("Enrolling ID #"); Serial.println(matricNo);

  // Send data to the server
  String fingerprintID = generateFingerprintID();

  // Finally, retrieve password
  Serial.println("Enter password:");
  char* password = getInput();

  // Send to server!
  // String data = "studentId=<TODO>" + "&fingerprint=" + String(fingerprintID);
  // Serial.print(data); 
  printToScreen("simulated server");
  // sendToServer(data);
}

#endif
