# Original by rainnw. Edited/updated by Dolorre.

# convert BIN GTI files to C++ arrays for Arduino

import sys

# Source file
input = "SAE.bin"
# Destination file
destination = "SAE.txt"

file = open(input,"r")

compiled = "const unsigned char gti[] PROGMEM = { "
 
col = 0

while 1==1:
   data = file.read(1)
   if data == "": break
   compiled = compiled + str(str(ord(data))+",")   
   col = col + 1
   if col == 90000: 
        compiled = compiled + str("\n")
        col = 0
compiled = compiled + str("};")

print ("Compile complete.")

o = open(destination, "w", encoding="utf-8")
o.write(compiled)
o.close()
print ("Written to "+destination+".")
file.close()
