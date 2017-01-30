#The Compiler
CC = g++

#Compiler Flags
CFLAGS = -w -c

#Header Files Required
_DEPS = main.cpp constants.h fireball.h fireball.cpp functions.h functions.cpp globals.h globals.cpp players.h players.cpp texture.h texture.cpp tile.h tile.cpp timer.h timer.cpp gamestate.h gamestate.cpp
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

#Directory to Search for SDL Include Files. Change to match your installation of SDL.
IDIR = /usr/local/include 

#Source File Directory
SRCDIR = ../src

#Directory to Search for Library Files. Change to match your installation of SDL.
LDIR = /usr/local/lib

#Libraries Required for Compilation
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

FINAL = CGProject

OBJ = main.o fireball.o functions.o globals.o players.o texture.o tile.o timer.o gamestate.o


all: $(FINAL)
	$(CC) $(OBJ) -L$(LDIR) -I$(IDIR) $(LIBS) -o $(FINAL)
	chmod +x $(FINAL) 
	mv ./$(FINAL) ../$(FINAL)

$(FINAL): $(DEPS)
	$(CC) $(DEPS) -L$(LDIR) -I$(IDIR) $(LIBS) $(CFLAGS)

.PHONY: clean

clean:
	rm *.o