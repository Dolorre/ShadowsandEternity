#include "globals.h"
#include "menu.h"
#include "game.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuPlay,
  stateMenuHelp,
  stateMenuCredits,
  stateGameEnded,
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
