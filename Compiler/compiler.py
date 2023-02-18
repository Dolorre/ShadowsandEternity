# Original by rainnw. Edited/updated by Dolorre.
# Compiles a CSV into byte code and then to an array

import os

# Source csv file: change csv_source to the file path of the .csv.
csv_source = "E:\Documents\Arduboy FX Games\ArduBoyGTI\silence.csv"

assert os.path.exists(csv_source), "File not found."

with open(csv_source, 'r') as source:
   file = source.readlines()
print("Source csv file found!")

# Destination bin file: change bin_source to the file path where you want the .bin.
bin_source = "E:\Documents\Arduboy FX Games\ArduBoyGTI\silence.bin"

# Destination txt file: change txt_source to the file path where you want the .txt.
txt_source = "E:\Documents\Arduboy FX Games\ArduBoyGTI\silence.txt"

rooms = []
room_type = []
room_label = []
room_size = []
room_address = []
room_exits = []
address = {}
compiled = ""
mode = 0

for i in range(0,len(file)):
   line = file[i].strip().split(",")
   mode = line[1]
   if mode.upper() == "ROOM":
       binary = "" 
       exit_a = line[2]
       exit_b = line[3]
       exit_a_description = line[4]
       exit_b_description = line[5]
       description = ",".join(line[6:]).rstrip()
       description = description.replace("||",",")
       binary = binary + exit_a_description + chr(0)
       binary = binary + exit_b_description + chr(0)
       binary = binary + description + chr(0)
       rooms.append(binary)
       room_type.append("room")
       room_label.append(line[0])
       room_exits.append([exit_a,exit_b])
   if mode.upper() == "SPECIAL":
       if line[2].upper() == "END":
             Line_text = []
             Line_text = line[0:4]
             binary = ""
             description = ",".join(Line_text[3:]).rstrip()
             description = description.replace("||",",")
             binary = binary + description + chr(0)
             rooms.append(binary)
             room_type.append("end")
             room_label.append(line[0])
             room_exits.append(['special','end'])
       if line[2].upper() == "TEXT":
             Line_text = []
             Line_text = line[0:4]
             binary = ""
             description = ",".join(Line_text[3:]).rstrip()
             description = description.replace("||",",")
             binary = binary + description + chr(0)
             rooms.append(binary)
             room_type.append("text")
             room_label.append(line[0])
             room_exits.append(['special','text'])
       if line[2].upper() == "JUMP":
             rooms.append("")
             room_type.append("jump")
             room_label.append(line[0])
             room_exits.append([line[3].rstrip(),line[3].rstrip()])
       if line[2].upper() == "EFFECT":
             rooms.append(line[3].rstrip())
             room_type.append("effect")
             room_label.append(line[0])
             room_exits.append([line[3].rstrip(),line[3].rstrip()])

         
print ("ASCII data converted. Indexing rooms complete.")

# Build a list of field lengths

for i in range(0,len(rooms)):
     size = 2
     if room_type[i] == "room":
         size = size + 2
         size = size + len(rooms[i])
     if room_type[i] == "end":
         size = size + 1
         size = size + len(rooms[i])
     if room_type[i] == "text":
         size = size + 1
         size = size + len(rooms[i])
     if room_type[i] == "jump":
         size = size + 3
     if room_type[i] == "effect":
         size = size + 2
     room_size.append(size) 

print ("Calculated field lenghs.")

# calculate room addresses

pc = 0

for i in range(0,len(rooms)):
     room_address.append(pc)
     pc = pc + room_size[i]
     
print ("Calculated field addresses.")

for i in range(0,len(rooms)):
     address[room_label[i]] = room_address[i]

print ("Label address dictionary built.")

for i in range(0,len(rooms)):
     if room_type[i] == "room":
       compiled = compiled + chr(address[room_exits[i][0]] >> 8) + chr(address[room_exits[i][0]] & 0xFF)
       compiled = compiled + chr(address[room_exits[i][1]] >> 8) + chr(address[room_exits[i][1]] & 0xFF)
       compiled = compiled + rooms[i].rstrip()
     if room_type[i] == "end":
       compiled = compiled + chr(255) + chr(255)
       compiled = compiled + chr(0)
       compiled = compiled + rooms[i].rstrip()
     if room_type[i] == "text":
       compiled = compiled + chr(255) + chr(255)
       compiled = compiled + chr(16)
       compiled = compiled + rooms[i].rstrip()
     if room_type[i] == "jump":
       compiled = compiled + chr(255) + chr(255)
       compiled = compiled + chr(5)
       compiled = compiled + chr(address[room_exits[i][0]] >> 8) + chr(address[room_exits[i][0]] & 0xFF)
     if room_type[i] == "effect":
       compiled = compiled + chr(255) + chr(255)
       compiled = compiled + chr(13)
       compiled = compiled + chr(int(rooms[i].rstrip()))

print ("Compile complete.")

o = open(bin_source,"w", encoding="utf-8")
o.write(compiled)
o.close()
print ("Written to "+bin_source+".")
print ("Final length was "+str(len(compiled))+".")

# Bin to txt conversion
print ("Beginning bin conversion.")

b_source = open(bin_source,'r', encoding='utf-8', newline='') 

bin_compiled = "const unsigned char gti[] PROGMEM = { "

col = 0

while 1==1:
   data = b_source.read(1)
   if data == "": break
   bin_compiled = bin_compiled + (str(ord(data))+",")
   col = col + 1
   if col == 90000: 
      compiled = compiled + "\n"
      col = 0
      
bin_compiled = bin_compiled + "};"

b_source.close()

print ("Compile complete.")

to = open(txt_source, "w")
to.write(bin_compiled)
to.close()
print ("Written to "+txt_source+".")

base = 12722
max = 28672
size = max - base
if len(compiled) > size:  print ("Warning: memory size exceeded by "+str(len(compiled) - size)+" bytes!")
