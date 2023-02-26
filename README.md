# Shadows and Eternity
Shadows and Eternity is a sci-fi text-based adventure game made for the Arduboy. Your goal is to survive the day, if you can.

This also happens to be a resurrection project of spaceneedle’s GameTextInterpreter (GTI) engine. I’ve used the update provided by the wonderful Mr.Blinky. I’m also working to update the engine and make some changes.

I hope in the end it’s a useful tool for making text-based games on the Arduboy!

--FEATURES--
* Text + branch (Player picks selection A or B)
* Text only fields
* Jumping
* Sound effects
* A start menu with graphics
* And more!

--- SAEGTI INSTRUCTIONS ---

What programs you’ll need:
Notepad++
Microsoft Excel (or other program that can export .csv files)
Python IDLE (or favorite code editing software that can handle Python)
Arduino 1.8.19 (set up with the Arduboy libraries, as well as Mr. Blinky’s Arduboy FX Arduino plugin) 

Creating the Game Text:
1.	Open GTI_FX_Example for examples on the different commands you can utilize in your game.
2.	Create a new document and set up your game text. You can refer to the SAEGTI Example CSV for examples. 
3.	Save often and save new versions at least every half hour, just in case you make mistakes.

Export CSV:
1.	Switch all (‘ or ’) to (').
2.	Switch all commas (,) to || and all quotation marks (“ and ” and ") to &&.
3.	Export the file to CSV and close the program.
4.	Open the CSV with Notepad++. 
5.	Do a find and replace all && to quotation marks. 
6.	Save the file and close it.

Compile CSV:
1.	Open compiler.py with the Python IDLE.
2.	Go to Options > Show Line Numbers and click on it.
3.	Replace the file path on line 7 with the name and location of your .csv file.
4.	Replace the file path on line 16 with the location you would like to store the final .txt file.
5.	Save the file.
6.	Click Run > Run Module.
7.	Wait for it to finish, then press any key to close it.

Update fxdata.txt:
1.	Navigate to the fxdata folder and open fxdata.txt.
2.	Replace the final line (uint8_t gti) with the text from the .txt file created earlier.
3.	Save the file and close it.

Compile the game:
1.	Open the SAEGTI.ino file and navigate to Tools > Build Arduboy FX data.
2.	If you have made any changes to the code, be sure to compile it by going to Sketch > Export compiled Binary.
3.	Once it has finished, you are ready to test your game! I suggest trying Brow1067’s Arduboy profiler/debugger: https://community.arduboy.com/t/arduboy-profiler-debugger.
4.	To use the debugger, simply drag the game .hex file into the window, followed by the fxdata.bin file. 
5.	You can easily speed up or slow down the game while running it with the slider bar in the Simulation section.
