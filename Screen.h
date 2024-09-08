#pragma once

/**
Generic print to STD OUT.
Temporarily uses Serial, will change to LCD.
*/
void printToScreen(char* data, bool noTerm = false) {
  if (noTerm) {
    Serial.print(data);
  } else {
    Serial.println(data);
  }
}
