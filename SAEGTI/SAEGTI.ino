// Arduboy GTI player by rainnw
// Some code used/modified from Sirène (Team A.R.G.)
// Some code from Pharap, Mr.Blinky, and brow1067

// Shadows and Eternity by Dolorre

#include "globals.h"
#include "game.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuPlay,
  stateMenuHelp,
  stateMenuCredits,
};

void setup() {
  arduboy.begin();
  FX::begin(FX_DATA_PAGE);    // initialise FX chip
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  FX::display(CLEAR_BUFFER);
}
