CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs 
LDFLAGS =`sdl2-config --cflags --libs` -lSDL2_ttf
INCLUDES = -I./SDL2_ttf 
EXEC = main1 main2
SRC = fonctions_fichers.c fonctions_SDL.c Interface_Start.c
SRC2 = fonctions_fichers.c fonctions_SDL.c main.c
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(EXEC)
main1: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
main2: $(OBJ2)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: 
	cleanrm -rf $(EXEC)
