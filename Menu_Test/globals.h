#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyFX.h>
#include <avr/pgmspace.h>

#include "fxdata/fxdata.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO              0  // stateMenuIntro
#define STATE_MENU_MAIN               1  // stateMenuMain
#define STATE_MENU_PLAY               2  // stateMenuPlay
#define STATE_MENU_HELP               3  // stateMenuHelp
#define STATE_MENU_CREDITS            4  // stateMenuCredits

#define STATE_GAME_ENDED              5  // stateGameEnded

Arduboy2 arduboy;

byte gameState = STATE_MENU_INTRO;     // start the game with the Dolorre logo
byte menuSelection = STATE_MENU_PLAY;  // START menu item is pre-selected

constexpr uint8_t menuOptions = 3;
uint8_t selectedIndex = 0;

// Integers
int x [2];
int y [2];

#endif
