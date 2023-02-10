# Original by rainnw. Edited/updated by Dolorre.

# convert BIN GTI files to C++ arrays for Arduino

# NOTE: This will take a while, quite a while depending on the length of the csv file.

import sys

# Source file
input = "sae.bin"

file = open(input,"r")
 
print ("const unsigned char gti[] PROGMEM = { ")

col = 0

while 1==1:
   data = file.read(1)
   if data == "": break
   sys.stdout.write(str(ord(data))+",")
   col = col + 1
   if col == 90000: 
        sys.stdout.write("\n")
        col = 0
print ("};")
