all: S0.exe

data.o: data.c
	gcc -Wall -Wextra -c data.c

trama.o: trama.c trama.h
	gcc -Wall -Wextra -c trama.c

dataFunc.o: dataFunc.c dataFunc.h
	gcc -Wall -Wextra -c dataFunc.c 
	
thread.o: thread.c thread.h
	gcc -Wall -Wextra -c thread.c -lpthread

connexio.o: connexio.c connexio.h
	gcc -Wall -Wextra -c connexio.c
	
llistaOrdenada.o: llistaOrdenada.c llistaOrdenada.h
	gcc -Wall -Wextra -c llistaOrdenada.c

S0.exe: data.o dataFunc.o trama.o connexio.o thread.o llistaOrdenada.o
	gcc data.o dataFunc.o connexio.o thread.o trama.o llistaOrdenada.o -Wall -Wextra -o S0.exe -lpthread

clean:
	rm -rf *.o S0.exe
