CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs 
LDFLAGS =`sdl2-config --cflags --libs` -lSDL2_ttf
INCLUDES = -I./SDL2_ttf 
EXEC = start main commuter help terrainfin
SRC = fonctions_fichers.c fonctions_SDL.c Interface_Start.c
SRC2 = fonctions_fichers.c fonctions_SDL.c main.c
SRC3 = fonctions_fichers.c fonctions_SDL.c Interface_Commuter.c
SRC4 = fonctions_fichers.c fonctions_SDL.c Help.c
SRC5 = fonctions_fichers.c fonctions_SDL.c terrainfin.c

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
OBJ4 = $(SRC4:.c=.o)
OBJ5 = $(SRC5:.c=.o)

all: $(EXEC)
start: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
main: $(OBJ2)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
commuter: $(OBJ3)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
help: $(OBJ4)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
terrainfin: $(OBJ5)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: 
	cleanrm -rf $(EXEC)
