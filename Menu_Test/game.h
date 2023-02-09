#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"

boolean objectVisible;

void stateMenuPlay()
{
  FX::drawBitmap(x[0],y[0],dolorreLogo,0,dbmNormal);
};

void stateGameEnded()
{
  FX::drawBitmap(x[0],y[0],theEnd,0,dbmNormal);
}

#endif
