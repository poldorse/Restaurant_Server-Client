all: Practica.exe

picard.o: picard.c
	gcc -Wall -Wextra -c picard.c

fitxer.o: fitxer.c fitxer.h
	gcc -Wall -Wextra -c fitxer.c

trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c

connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c

Practica.exe: picard.o fitxer.o connexio.o trama.o
	gcc picard.o fitxer.o trama.o connexio.o -Wall -Wextra -o S0.exe

clean:
	rm -rf *.o S0.exe
