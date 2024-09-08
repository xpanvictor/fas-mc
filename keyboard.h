
#pragma once;

#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
char keys[ROWS][COLS] = {
  { 1, 2, 3, 4 },
  { 5, 6, 7, 8 },
  { 9, 10, 11, 12 },
  { 13, 14, 15, 16 },
};
byte rowPins[ROWS] = { 13, 12, 11, 10 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 };      //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ASCII characters
// 0x08 BS  <backspace>
// 0x0A LF  <newline>
// 0x0D CR  <carriage return>
// 0x11 DC1 <device control 1>
// 0x12 DC1 <device control 2>
// 0x13 DC1 <device control 3>
// 0x14 DC1 <device control 4>
// 0x7F DEL <delete>

#define backspace 0x08
#define reset 0x11
#define dial 0x12
#define enter 0x0A

// 1ABC 2DEF 3GHI <reset>
// 4JKL 5MNO 6PQR <dial>
// 7STU 8VWX 9YZ. <backspace>
// <sp>  0   +-   <enter>

const char keyCharArray[16][5] PROGMEM = {
  "1ABC",
  "2DEF",
  "3GHI",
  "\x11",
  "4JKL",
  "5MNO",
  "6PQR",
  "\x12",
  "7STU",
  "8VWX",
  "9YZ.",
  "\x08",
  " ",
  "0",
  "+-",
  "\x0A",
};

// Only generating a final Char
char finalText[80] = "";
size_t finalTextIndex = 0;

char mygetKey() {
  const unsigned long keyDelay = 500ul;  //maximum delay between multiple presses of same key
  static unsigned long keyTimer;
  static size_t keyCharIndex = 0;  //index of current character for multi-character key
  static char keyPrevious = '\0';  //previous key pressed
  static char keyPending = '\0';   //temporary storeage for key pressed within multi-charactere delay for another key
  char key;
  char keyChar = '\0';  //character to be returned from this function

  if (keyPending == '\0') {  //check for key pressed during multi-character delay for another key
    key = keypad.getKey();
  } else {
    key = keyPending;
    keyPending = '\0';
  }

  if (key) {
    if (keyPrevious == '\0') {
      if (strlen_P(keyCharArray[key - 1]) == 1) {
        //key represents a single character
        keyChar = (char)pgm_read_byte(&keyCharArray[key - 1][0]);
      } else {
        //key represents multiple characters
        keyTimer = millis();
        keyPrevious = key;
        keyCharIndex = 0;
      }
    } else {
      if (keyPrevious == key) {  //same key has been pressed multiple times
        if ((millis() - keyTimer) < keyDelay) {
          keyCharIndex++;  //advance to next character for key
          if (keyCharIndex >= strlen_P(keyCharArray[key - 1])) {
            keyCharIndex = 0;
          }
          keyTimer = millis();
        }
      } else {                                                                        //key pressed during the timer delay for another key
        keyChar = (char)pgm_read_byte(&keyCharArray[keyPrevious - 1][keyCharIndex]);  //return character from previous key
        keyPrevious = '\0';
        keyPending = key;  //save current key to be processed next time function is called
      }
    }
  }
  if ((keyPrevious != '\0') && ((millis() - keyTimer) > keyDelay)) {  //return multi-character key press when timer runs out
    keyChar = (byte)pgm_read_byte(&keyCharArray[keyPrevious - 1][keyCharIndex]);
    keyPrevious = '\0';
  }
  return keyChar;
}

char waitForKeyPress() {
  char key = '\0';
  while (key == '\0') { // Loop until a key is pressed
    key = mygetKey();   // Replace with your actual key reading function
  }
  return key; // Return the key that was pressed
}

/**
  Retrieve a bunch of input from user
*/
char* getInput() {
  char* tmpText = NULL;
  Serial.print(F("current text: "));
  while (1) {
    char key = mygetKey();
    switch (key) {
      case '\0':
        break;
      case enter:
        // Allocate memory for tmpText based on the length of finalText
        tmpText = (char*)malloc(finalTextIndex + 1); // +1 for the null terminator
        if (tmpText != NULL) {
          strncpy(tmpText, finalText, finalTextIndex);
          tmpText[finalTextIndex] = '\0'; // Null-terminate the string
        }
        // Reset finalText for future use
        finalTextIndex = 0;
        finalText[0] = '\0';
        Serial.println();
        return tmpText;
      case backspace:
        if (finalTextIndex > 0) {
          finalTextIndex--;
        }
        Serial.println();
        Serial.print(F("current text: "));
        Serial.write(finalText, finalTextIndex);
        break;
      case dial:
        break;
      case reset:
        finalTextIndex = 0;
        finalText[0] = '\0';
        Serial.println();
        Serial.print(F("current text: "));
        Serial.write(finalText, finalTextIndex);
        break;
      default:
        finalText[finalTextIndex] = key;
        finalTextIndex++;
        if (finalTextIndex >= sizeof(finalText)) {
          finalTextIndex = sizeof(finalText) - 1;
        }
        Serial.print(finalText[finalTextIndex - 1]);
        break;
    }
  }
}
