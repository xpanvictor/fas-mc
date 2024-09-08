#pragma once

#include "FingerprintVerification.h"
#include "keyboard.h"
#include "Screen.h"

void markAttendance(char* attendanceData) {}

void classMode() {
  printToScreen("Class mode initiated");
  printToScreen("Please enter class code:");
  char* classCode = getInput();
  
  // Flow here is keep registering until input of q
  while(1) {
    printToScreen("Starting class with code: ", true);
    printToScreen(classCode);

    printToScreen("Enter Q to end class. Anything else for attendance: ", true);
    char mode = waitForKeyPress();
    switch(mode) {
      case 'Q':
        return;
      default:
        markAttendance("");
        printToScreen("Simulating sending attendance data to server.");
        delay(3000);
    }
  }
}
