#include "dataFunc.h"

int fd = -1;
char *comanda, *auxp, *auxString;

int obtDades(Dades *dades){
	int count = 0;
  char aux_char = '\0', aux_port[20];
	fd = open("configData.txt", O_RDONLY);
  if (fd <= 0) return 0;
	count = 0;
  read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    dades->ip[count] = aux_char;
    read(fd, &aux_char, 1);
    count++;
  }
	dades->ip[count-1]= '\0';
	count = 0;
	read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    aux_port[count] = aux_char;
    read(fd, &aux_char, 1);
    count++;
  }  
	dades->portPicard = atoi(aux_port);
	count = 0;
	aux_port[0]='\0';
  read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    aux_port[count] = aux_char;
    read(fd, &aux_char, 1);
    count++;
  }
  aux_port[count]='\0';  
  dades->portEnterprise = atoi(aux_port);
	close (fd);

	return 1;
}


int printar(char *frase){
	write(1,frase,strlen(frase));
	return 1;
}
