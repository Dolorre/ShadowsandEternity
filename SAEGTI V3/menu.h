#ifndef MENU_H
#define MENU_H

#include "globals.h"

void drawTitleScreen()
{
  FX::drawBitmap(x[0],y[0],saeTitle,0,dbmNormal);
}

void stateMenuIntro()
{
  globalCounter++;
  FX::drawBitmap(x[0],y[0],dolorreLogo,0,dbmNormal);
  if (globalCounter > 180)
  {
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  drawTitleScreen();
  
  static const uint8_t lineCoordsX[menuOptions] PROGMEM { 14, 52, 94 };
  static const uint8_t lineCoordsY[menuOptions] PROGMEM { 62, 62, 62 };
  
  // Read the line coordinates from the progmem arrays
  // (This is usually cheaper than using lots of if statements)
  const uint8_t lineX = pgm_read_byte(&lineCoordsX[selectedIndex]);
  const uint8_t lineY = pgm_read_byte(&lineCoordsY[selectedIndex]);
  
  // Draw the line
  FX::drawBitmap(lineX,lineY,selectionLine,0,dbmMasked);
  
  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 4))
  {
    menuSelection++;
    selectedIndex++;
  }
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 2)) 
  {
    menuSelection--;
    selectedIndex--;
  }
  if (arduboy.justPressed(A_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  FX::drawBitmap(x[0],y[0],helpText,0,dbmNormal);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuCredits()
{
  FX::drawBitmap(x[0],y[0],creditsText,0,dbmNormal);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

#endif
