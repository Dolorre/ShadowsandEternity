#ifndef GAME_H
#define GAME_H

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

void stateMenuPlay() {
  uint16_t pc = 0;
 while(true) {  
  FX::seekData(gti + pc);                                                                         // Search for selected byte
  uint16_t type = FX::readPendingLastUInt16();
  pc++;                                                                                           // bump program counter
  col = 0;                                                                                        // reset columns in text display
  if(type == 65535) {                                                                             // SPECIAL Frame Detected
     pc++;                                                                                        // bump program counter
     FX::seekData(gti + pc);                                                                      // Search for selected byte
     uint8_t mode = FX::readEnd();                                                                // get the special packet mode
     
     switch (mode) {                                                                              // switch based on what mode the frame is

       // 0x00 - Game Over

       case 0:                                                                                    // Game Over handler
           while(true) {                                                                          // loop over text until we hit a null
             pc++;                                                                                // bump program counter
             FX::seekData(gti + pc);                                                              // Search for selected byte
             uint8_t buff = FX::readEnd();                                                        // read a chracter
             printer(buff);                                                                       // print out the text using our text output handler
             if(buff == 0) { break; }                                                             // is it a null? then we are done printing text
           }
           arduboy.print("*GAME OVER*");                                                          // print generic Game Over message
           #if USE_SERIAL == ON
           Serial.print("*GAME OVER*");                                                           // if the serial port is turned on, print message over serial
           #endif
           FX::display();                                                                         // Display the game over text
           anykey();                                                                              // wait for anykey
           col = 0;                                                                               // reset the columns (probably not needed)
           return;                                                                                // quit out of the VM
           break;                                                                                 // break that will not be executed

       // 0x15 - Ending

       case 21:                                                                                   // Game ending handler
           while(true) {                                                                          // loop over text until we hit a null
             pc++;                                                                                // bump program counter
             FX::seekData(gti + pc);                                                              // Search for selected byte
             uint8_t buff = FX::readEnd();                                                        // read a chracter
             printer(buff);                                                                       // print out the text using our text output handler
             if(buff == 0) { break; }                                                             // is it a null? then we are done printing text
           }
           anykey();                                                                              // Wait for anykey
           arduboy.clear();                                                                       // Clear the screen
           FX::drawBitmap(x[0],y[0],theEnd,0,dbmNormal);                                          // Display ending graphic
           FX::display();                                                                         // Display the end graphic
           endinganykey();                                                                        // Wait for ending anykey
           col = 0;                                                                               // reset the columns (probably not needed)
           gameState = STATE_MENU_MAIN;                                                           // Set the game state to the main menu
           return;                                                                                // quit out of the main game state
           
       // 0x05 - Jump    
           
       case 5:                                                                                    // Jump handler
           pc++;                                                                                  // bump the program counter
           FX::seekData(gti + pc);                                                                // Search for selected byte
           pc = FX::readPendingLastUInt16();
           break;                                                                                 // switch break
           
       // 0x0D - Effects Library    

       case 13:                                                                                   // Effects Handler
       #if SFXLIB == ON                                                                           // If our effects library is switched on
            pc++;                                                                                 // Bump program counter
            FX::seekData(gti + pc);                                                               // Search for selected byte
            effect = FX::readEnd();                                                               // Get effect type
            
            switch(effect) {                                                                      // Effect switcher
            
               // 0x00 - Low pitched rumbling sound
            
               case 0:                                                                            // rumble handler
                   #if SOUND == ON                                                                // Is sound turned on?
                   for(int x = 60; x < 150; x++) {                                                // Low frequency sweep 
                   sound.tone(x, 10);  delay(10); }                                               // Play our low frequency sweep
                   #endif                                                                         // end sound check
                   break;                                                                         // switch break
                  
               // 0x01 - Random lightning flash   
                   
               case 1:                                                                            // Random lightning flash 
                   for(int x = 0; x < 50; x++) {                                                  // Small loop for our flashes
                     if(random(0,10) == 1) {                                                      // 1 in 10 chance of a flash
                            arduboy.fillScreen(WHITE);                                            // Fill screen with white
                            FX::display();                                                        // push it out
                     } 
                     else {                                                                       // Not a 1 in 10 chance?
                            arduboy.fillScreen(BLACK);                                            // Make screen black
                            FX::display();                                                        // Push it out
                     } 
                     delay(20);
                   }
                   break;                                                                         // switch break
            }  
            pc++;                                                                                 // Bump program counter
       #else                                                                                      // Otherwise, is the SFX mode disabled?
         pc++; pc++;                                                                              // Increment program counter so we don't lose position
       #endif
            break;                                                                                // switch break

       // 0x10 - Display page of text and wait for any key
       
       case 16:                                                                                   // text handler
           while(true) {                                                                          // print some text until we find a null
             pc++;                                                                                // Bump program counter
             FX::seekData(gti + pc);                                                              // Search for selected byte
             uint8_t buff = FX::readEnd();                                                        // Read a character
             printer(buff);                                                                       // Send text off to our printer 
             if(buff == 0) { break; }                                                             // Is it null? then break out of loop
           }         
           anykey();                                                                              // Wait for any key 
           pc++;                                                                                  // Bump program counter
           break;                                                                                 // Switch case break
    }
  }
  
  // We reuse the 'type' uint16_t variable as jump a's address
  
  else {    

     // Jump A description buffer
    
      pc++;                                                                                                   // bump program counter
      FX::seekData(gti + pc);                                                                                 // Search for selected byte
      uint16_t alterexit = FX::readPendingLastUInt16();
      pc++; pc++;                                                                                             // bump program counter
      int i = 0;                                                                                              // initalize i (to keep track of array position)
      while(true) {                                                                                         // fill jump a description buffer
        FX::seekData(gti + pc);                                                                               // Search for selected byte
        uint8_t buff = FX::readEnd();                                                                         // get a character
        if(buff == 0) { exita[i] = 0; break; }                                                                // Is it null? append the null to array then stop
        exita[i] = buff;                                                                                      // fill array with newest character
        i++; pc++;                                                                                            // bump array position and program counter
      }

     // Jump B description buffer
      
      pc++;                                                                                                   // bump program counter
      i = 0;                                                                                                  // reset array position
      while(true) {                                                                                           // fill jump b description buffer 
        FX::seekData(gti + pc);                                                                               // Search for selected byte
        uint8_t buff = FX::readEnd();                                                                         // get a character
        if(buff == 0) { exitb[i] = 0; break; }                                                                // Is it null? append the null to array then stop
        exitb[i] = buff;                                                                                      // fill array with newest character
        i++; pc++;                                                                                            // bump array position and program counter
      } 
      
      int x = 0;                                                                                              // define x (we could probably still reuse i?)
 
      // Main description printing (since the description goes before the jump selections)
      
      while(true) {                                                                                              // print the main description text, null terminated
             pc++;                                                                                            // bump program counter
             FX::seekData(gti + pc);                                                                          // Search for selected byte
             uint8_t buff = FX::readEnd();                                                                    // get character from main description
             printer(buff);                                                                                   // Print out our newest character
             if(buff == 0) { break; }                                                                         // did we find a null? stop printing description
      }  
      pc++;
      #if SOUND == ON
      sound.tone(1318, 50); 
      #endif
      arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); FX::display();
      if(arduboy.getCursorY() < 48) { arduboy.print("\n"); 
      #if USE_SERIAL == ON
      Serial.println();
      #endif
      } 
        
      printer('A'); printer(']'); printer(' '); FX::display();
      #if USE_SERIAL == ON
      Serial.print("\nA] ");
      #endif
       x = 0;
       while(true) { 
             printer(exita[x]);
             if(exita[x] == 0) { break; } 
             x++; 
      }  
      x = 0; 
      #if SOUND == ON
      sound.tone(1318, 50); 
      #endif
      arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); FX::display();
      printer('B'); printer(']'); printer(' '); FX::display();
      #if USE_SERIAL == ON
      Serial.print("\nB] ");
      #endif      
       while(true) { 
             printer(exitb[x]);
             if(exitb[x] == 0) { break; } 
             x++;
      } 
      arduboy.fillRect(arduboy.getCursorX(),arduboy.getCursorY(),8,8,BLACK); FX::display();
      int selection = select();
      if(selection == 0) { pc = type; } 
      if(selection == 1) { pc = alterexit; } 
      arduboy.clear(); 
      FX::display();
      col = 0;
  }
}
  }
#endif
