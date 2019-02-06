/* 
 *  ADVENTURE GAME ARDUINO
 *  Creator : Thomas Cibils
 *  Last update : 05.02.2019
 *  FastLED tuto : https://github.com/FastLED/FastLED/wiki/Basic-usage - used for WS2812B 5050 RGB LED Strip 5M 150 300 Leds 144 60LED/M Individual Addressable 5V
 *  */

#include <TimerOne.h>
#include "FastLED.h"

// LED MATRIX CODE
const byte numberOfRows = 10;                          // Number of rows
const byte numberOfColumns = 6;                       // Number of coumns
const byte NUM_LEDS = numberOfRows * numberOfColumns; // Number of LEDs

CRGB leds[NUM_LEDS];                                          // Defining leds table for FastLed
#define DATA_PIN 6                                            // Output pin for FastLed

// LED Matrix
// top column is from 0 to 7, bottom one from 56 to 63 (for a 8x8 matrix)
byte LEDMatrix[numberOfRows][numberOfColumns] =
{
  {0, 1, 1, 1, 3, 1},
  {0, 0, 1, 3, 3, 1},
  {1, 0, 1, 0, 1, 1},
  {1, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 0, 1},
  {1, 0, 0, 2, 0, 1},
  {1, 0, 1, 1, 0, 1},
  {0, 0, 1, 0, 0, 1},
  {1, 1, 1, 0, 1, 1},
  {0, 0, 0, 0, 0, 0}
};


byte tempMap[20][20] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/*
// To be correctly field
// The adventurer will walk on it
byte Map[100][12] =
{
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1},
  {0, 1, 1, 1, 3, 1, 0, 1, 1, 1, 3, 1}
};
*/

// Original colours for leds.
const byte Wall = 0;
const byte Passage = 1;
const byte Blue = 2;
const byte Red = 3;
const byte Green = 4;
const byte Purple = 5;


// Pin used from the arduino
const unsigned int leftButton = A0;        // Input pin for button Left
const unsigned int upButton = A1;          // Input pin for button Up
const unsigned int rightButton = A3;       // Input pin for button Right
const unsigned int downButton = A4;        // Input pin for button Down
const unsigned int aButton = A0;           // Input pin for button A
const unsigned int bButton = A1;           // Input pin for button B

/*
struct pointOnMatrix {
  int lineCoordinate;
  int columnCoordinate;
};
*/

unsigned long lastMillis = 0;

int leftButtonValue = LOW;
int rightButtonValue = LOW;
int lastLeftButtonValue = LOW;
int lastRightButtonValue = LOW;

void setup() {

  Serial.begin(9600);

  // Set matrix pins to output
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Set button pins to input
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
}

void loop() {
  
  outputDisplay();
  delay(1);
}

// Makes the whole "LEDMatrix" equals to 0, i.e. each LED is off
void clearLEDMatrix() {
  // Just seting le LEDmatrix to Wall
  for (byte i = 0; i < numberOfRows; i++)  {
    for (byte j = 0; j < numberOfColumns; j++) {
      LEDMatrix[i][j] = Wall;
    }
  }
}


// We update the physical display of the LED matrix, based on the LEDMatrix
void outputDisplay() {
  for(byte rowIndex = 0; rowIndex < numberOfRows; rowIndex++) {
    for(byte columnIndex = 0; columnIndex < numberOfColumns; columnIndex++) {
      // Useful because of the way my matrix is soldered.
      // So we'll invert one column every two compared to our digital matrix
      // If we're on an even column, we're fine, everything is straightfoward
      if(columnIndex%2 == 0) {
        
        if(LEDMatrix[rowIndex][columnIndex] == Wall) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::White;}
        if(LEDMatrix[rowIndex][columnIndex] == Passage) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::Black;}
        if(LEDMatrix[rowIndex][columnIndex] == Green) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::Green;}
        if(LEDMatrix[rowIndex][columnIndex] == Blue) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::Blue;}
        if(LEDMatrix[rowIndex][columnIndex] == Red) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::Red;}
        if(LEDMatrix[rowIndex][columnIndex] == Purple) {leds[(columnIndex + 1)*numberOfRows - rowIndex - 1] = CRGB::Purple;}
      }
      // If we're on an uneven column, we do a mathematical trick to invert it
      else if(columnIndex%2 == 1) {
        if(LEDMatrix[rowIndex][columnIndex] == Wall) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::White;}
        if(LEDMatrix[rowIndex][columnIndex] == Passage) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::Black;}
        if(LEDMatrix[rowIndex][columnIndex] == Green) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::Green;}
        if(LEDMatrix[rowIndex][columnIndex] == Blue) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::Blue;}
        if(LEDMatrix[rowIndex][columnIndex] == Red) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::Red;}
        if(LEDMatrix[rowIndex][columnIndex] == Purple) {leds[columnIndex*numberOfRows + rowIndex] = CRGB::Purple;}
      }
    }
  }
  
  // Display the matrix physically
  FastLED.show(); 
}

// We update the digital display of the LED matrix
void digitalOutputDisplay() {
  Serial.print("\n We print digitally the current theoritical state of the LED Matrix : \n");
  for (byte i = 0; i < numberOfRows; i++) {
    for (byte j = 0; j < numberOfColumns; j++) {
      Serial.print(LEDMatrix[i][j]);
      if (j < numberOfColumns - 1) {
        Serial.print(", ");
      }
      else {
        Serial.print("\n");
      }
    }
  }
}

// Updating the LED Matrix after each step
void updateLEDMatrix() {
}


// We end the game with a curtain of light
void endGame() {

  // Serial.print("\n GAME OVER \n");
  delay(1000);
  clearLEDMatrix();
  // We light up the rows one by one, with .2 sec of delay between each
  for (byte i = 0; i < numberOfRows; i++) {
    for (byte j = 0; j < numberOfColumns; j++) {
      LEDMatrix[i][j] = Red;
    }
      outputDisplay();
    
    delay(500);
  }
  // It stays on for 4 seconds
  delay(3500);

}
