#ifndef FINGERPRINT_VERIFICATION_H
#define FINGERPRINT_VERIFICATION_H

#include <Adafruit_Fingerprint.h>
#include "ServerCommunication.h"

extern Adafruit_Fingerprint finger;

void verifyFingerprint() {
  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz(1) != FINGERPRINT_OK) return;

  if (finger.fingerFastSearch() == FINGERPRINT_OK) {
    Serial.print("Found ID #"); Serial.println(finger.fingerID);  
    
    // Send attendance to server
    String data = "studentId=" + String(finger.fingerID) + "&attendance=true";
    sendToServer(data);
  } else {
    Serial.println("Fingerprint not found");
  }
}

#endif
