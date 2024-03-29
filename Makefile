CC=gcc
CFLAGS=-Wall
LIBS=
EXEC=dada

all: $(EXEC)

dada: src/dada.o src/des.o src/regles.o src/jeu.o src/pipes.o
	$(CC) $(CFLAGS) $(LIBS) src/dada.o src/des.o src/regles.o src/jeu.o src/pipes.o -o dada
	
dada.o: src/dada.c src/headers/dada.h src/headers/des.h src/headers/regles.h src/headers/jeu.h src/headers/pipes.h
	$(CC) $(CFLAGS) $(LIBS) -c src/dada.c
	
des.o: src/des.c src/headers/des.h
	$(CC) $(CFLAGS) $(LIBS) -c src/des.c
	
regles.o: src/regles.c src/headers/regles.h src/headers/jeu.h
	$(CC) $(CFLAGS) $(LIBS) -c src/regles.c

pipes.o: src/pipes.c src/headers/pipes.h
	$(CC) $(CFLAGS) $(LIBS) -c src/pipes.c
		
jeu.o: src/jeu.c src/headers/des.h src/headers/regles.h src/headers/jeu.h src/header/dada.h
	$(CC) $(CFLAGS) $(LIBS) -c src/jeu.c
	
clean:
	rm -rf src/*.o src/*~ src/headers/*~
	
mrproper:
	make clean
	rm -rf $(EXEC)

doxygen:
	doxygen doxygen-config
