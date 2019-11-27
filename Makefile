CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs 
LDFLAGS =`sdl2-config --cflags --libs` -lSDL2_ttf
INCLUDES = -I./SDL2_ttf 
EXEC = main
SRC = fonctions_fichers.c fonctions_SDL.c main.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: 
	cleanrm -rf $(EXEC)
