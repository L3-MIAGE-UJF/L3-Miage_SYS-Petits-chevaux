CC=gcc
CFLAGS=-Wall
LIBS=
EXEC=dada

all: $(EXEC)

dada: src/dada.o src/des.o src/regles.o
	$(CC) $(CFLAGS) $(LIBS) src/dada.o src/des.o src/regles.o -o bin/dada
	
dada.o: src/dada.c src/dada.h src/des.h src/regles.h
	$(CC) $(CFLAGS) $(LIBS) -c src/dada.c
	
des.o: src/des.c src/dada.h src/des.h src/regles.h
	$(CC) $(CFLAGS) $(LIBS) -c src/des.c
	
regles.o: src/regles.c src/dada.h src/des.h src/regles.h
	$(CC) $(CFLAGS) $(LIBS) -c src/regles.c
	
clean:
	rm -rf src/*.o src/*~
	
mrproper:
	make clean
	rm -rf bin/$(EXEC)
