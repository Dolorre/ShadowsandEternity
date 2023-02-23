#ifndef GLOBALS_H
#define GLOBALS_H

#include <EEPROM.h>
#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyFX.h>
#include <ArduboyTones.h>
#include <avr/pgmspace.h>

#include "fxdata/fxdata.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO              0  // stateMenuIntro
#define STATE_MENU_MAIN               1  // stateMenuMain
#define STATE_MENU_PLAY               2  // stateMenuPlay
#define STATE_MENU_HELP               3  // stateMenuHelp
#define STATE_MENU_CREDITS            4  // stateMenuCredits

#define ON 1
#define OFF 0

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

byte gameState = STATE_MENU_INTRO;     // start the game with the Dolorre logo
byte menuSelection = STATE_MENU_PLAY;  // START menu item is pre-selected

byte globalCounter = 0;

constexpr uint8_t menuOptions = 3;
uint8_t selectedIndex = 0;

// Integers for the X and Y of images
int x [2];
int y [2];

// System variables
uint8_t state = 0;
uint16_t room = 0;
uint8_t inst = 0;
uint8_t col = 0;
uint8_t row = 0;
uint8_t effect = 0;

uint8_t bt_a = 0;
uint8_t bt_b = 0;

unsigned char exita[80] = "";
unsigned char exitb[80] = "";

constexpr uint8_t charsPerLine = 21;
constexpr uint8_t linebufferSize = charsPerLine + 1; // one extra to detect end of line word break
constexpr uint8_t linebufferLastPos = charsPerLine; 
static uint8_t lineBuffer[linebufferSize];

// Game options
// Interpreter size tuning (turning off some interpreter support can save PROGMEM memory, but code must not contain related bytecodes (unless stated!)

#define SOUND ON             // 574 bytes (If support is disabled, bytecode is skipped properly)
#define USE_SERIAL OFF       // 182 bytes (no impact on bytecode interpreting)

#define VARIABLES ON
#define MUSIC ON
#define SFXLIB ON            // 496 bytes (If support is disabled, bytecode is skipped properly)
#define VECTOR ON

//void settings() { anykey(); } 

void printer(uint8_t character) {
    lineBuffer[col] = character;
    if ((character >= 32) & (col < (linebufferLastPos))) { //return no special characters and buffer not full
        ++col;
        return;  
    }
    if (arduboy.getCursorY() >= HEIGHT) {
        for (uint16_t i = 0; i < HEIGHT * WIDTH / 8 - WIDTH; i++) arduboy.sBuffer[i] =  arduboy.sBuffer[i+128]; //scroll up
        for (uint8_t i = 0; i < WIDTH; i++) arduboy.sBuffer[HEIGHT * WIDTH / 8 - WIDTH + i] = 0; //clear bottom line
        arduboy.setCursor(arduboy.getCursorX(),HEIGHT - 8);
    }
    uint8_t brk = col;
    while (brk> 0) {
        if (lineBuffer[brk] > 32) --brk;
        else break;
    }
    if (brk == 0) brk = col; //no word break
    if (brk == linebufferLastPos) {
        --brk; // exclude 1st character of next line
        if (lineBuffer[linebufferLastPos] == 32); --col; //remove space at start of next line
    }
    for (uint8_t i = 0; i <= brk; i++) {
        character = lineBuffer[i];
        if(character >= 32) 
        {
            arduboy.print((char)character);
            #if USE_SERIAL == ON
            Serial.print((char)character);
            #endif 
        }
        #if SOUND == ON
        sound.tone(1318, 2);
        #endif
        arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,WHITE); 
        FX::display();
        delay(50);
    }
    col -= brk; // remaining characters for next line
    for (uint8_t i = 0; i <= col; i++) lineBuffer[i] = lineBuffer[brk+i+1]; //move remaining character to start of buffer 
    arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); arduboy.println();
    #if USE_SERIAL == ON
    Serial.print("\n"); 
    #endif
}

uint8_t select() { 
  uint8_t c = 0; uint8_t blink = 0; 
  #if SOUND == ON
     sound.tone(1318, 50);  delay(50);
    sound.tone(400, 50); delay(50);
    sound.tone(600, 50); delay(50); 
  #endif
  while(1) { 
   if(arduboy.pressed(B_BUTTON)) { return 1; } 
   if(arduboy.pressed(A_BUTTON)) { return 0; } 
   
       c++; 
    if(c > 40) { 
       if(blink == 1) {  
         arduboy.fillRect(120,55,10,10,WHITE); 
         FX::display(); 
         blink = 0; } 
       else { 
         arduboy.fillRect(120,55,10,10,BLACK); 
         FX::display();  
         blink = 1; 
       } 
     c = 0;
   }    
  delay(10); 
  }
}

void anykey() { 
  arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); FX::display(); 
  #if SOUND == ON
    sound.tone(600, 50);  delay(50);
    sound.tone(1318, 50); delay(50);
    sound.tone(900, 50); delay(50);
  #endif
    uint8_t c = 0;
    uint8_t blink = 0;  
  while(1) { 
   if(arduboy.pressed(B_BUTTON) || arduboy.pressed(A_BUTTON)) { break; } 
   #if SERIAL == ON
   if(Serial.available()) { Serial.read(); Serial.read(); Serial.read(); break; } 
   #endif
    c++; 
    if(c > 40) { 
       if(blink == 1) {  
         arduboy.fillRect(120,55,10,10,WHITE); 
         FX::display(); 
         blink = 0; } 
       else { 
         arduboy.fillRect(120,55,10,10,BLACK); 
         FX::display();  
         blink = 1; 
       } 
     c = 0;
   }
   delay(10);    
   }
  arduboy.clear(); FX::display();
  #if SERIAL == ON
  Serial.println("\n"); 
  #endif
}

void endinganykey() { 
  arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); FX::display();
  #if SOUND == ON
    sound.tone(600, 50);  delay(50);
    sound.tone(1318, 50); delay(50);
    sound.tone(900, 50); delay(50);
  #endif
    uint8_t c = 0;
    uint8_t blink = 0;  
  while(1) { 
   if(arduboy.pressed(B_BUTTON) || arduboy.pressed(A_BUTTON)) { break; } 
   #if SERIAL == ON
   if(Serial.available()) { Serial.read(); Serial.read(); Serial.read(); break; } 
   #endif
    c++; 
    if(c > 40) { 
       if(blink == 1) {  
         arduboy.fillRect(125,60,1,1,WHITE); 
         FX::display(); 
         blink = 0; } 
       else { 
         arduboy.fillRect(120,55,10,10,BLACK); 
         FX::display();  
         blink = 1; 
       } 
     c = 0;
   }
   delay(10);    
   }
  arduboy.clear(); FX::display();
  #if SERIAL == ON
  Serial.println("\n"); 
  #endif
}

#endif
