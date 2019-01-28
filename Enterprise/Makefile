all: S0.exe

enterprise.o: enterprise.c
	gcc -Wall -Wextra -c enterprise.c -lpthread

funcions.o: funcions.c funcions.h
	gcc -Wall -Wextra -c funcions.c
	
connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c
	
trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c

thread.o: thread.c thread.h
	gcc -Wall -Wextra -c thread.c -lpthread
	
llista.o: llista.c llista.h
	gcc -Wall -Wextra -c llista.c


S0.exe: enterprise.o funcions.o connexio.o trama.o thread.o llista.o
	gcc enterprise.o funcions.o connexio.o thread.o trama.o llista.o -Wall -Wextra -o S0.exe -lpthread

clean:
	rm -rf *.o S0.exe
