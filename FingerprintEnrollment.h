#ifndef FINGERPRINT_ENROLLMENT_H
#define FINGERPRINT_ENROLLMENT_H

#include <Adafruit_Fingerprint.h>
#include "ServerCommunication.h"

extern Adafruit_Fingerprint finger;

void enrollFingerprint() {
  uint8_t id = 1;  // This ID can be dynamically assigned or retrieved from the server
  
  Serial.print("Enrolling ID #"); Serial.println(id);

  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz(1) != FINGERPRINT_OK) return;
  if (finger.createModel() != FINGERPRINT_OK) return;

  Serial.println("Fingerprint enrolled!");

  // Send data to the server
  String data = "studentId=" + String(id) + "&fingerprint=" + String(finger.fingerID);
  sendToServer(data);
}

#endif
