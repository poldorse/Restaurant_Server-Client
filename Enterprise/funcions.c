#include "funcions.h"

int fd = -1;


int obtDadesEnterprise(DadesConfigEnterprise *dades, char nomF[20]){
  int res = 0;
  int count = 0;
  char aux_char = '\0', aux[20];
	aux[0] = '\0';

  fd = open(nomF, O_RDONLY);
  if (fd <= 0) return 0;
	dades->nomRestaurant = NULL;
	dades->nomRestaurant = malloc(sizeof(char));
	res = read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    dades->nomRestaurant[count] = aux_char;
		dades->nomRestaurant = realloc(dades->nomRestaurant, (count+1)*sizeof(char));
    res = read(fd, &aux_char, 1);
    count++;
	}
	dades->nomRestaurant[count] = '\0';
  count = 0;
	res = read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    aux[count] = aux_char;
    res = read(fd, &aux_char, 1);
    count++;
  }
	dades->segons = atoi(aux);
	aux[0] = '\0';
	count = 0;
  res = read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    dades->ipdata[count] = aux_char;
    res = read(fd, &aux_char, 1);
    count++;
  }
	dades->ipdata[count-1]='\0';
	count = 0;
  res = read(fd, &aux_char, 1);
  while (aux_char != '\n') {
    aux[count] = aux_char;
    res = read(fd, &aux_char, 1);
    count++;
  }
	dades->portdata = atoi(aux);
	aux[0] = '\0';
	count = 0;
	res = read(fd, &aux_char, 1);
	while (aux_char != '\n') {
		dades->ippicard[count] = aux_char;
		res = read(fd, &aux_char, 1);
		count++;
	}
	dades->ippicard[count-1]='\0';
	count = 0;
	res = read(fd, &aux_char, 1);
	while (res != 0 || aux_char != '\n') {
		aux[count] = aux_char;
		res = read(fd, &aux_char, 1);
		count++;
	}
	aux[count]='\0';
  dades->portpicard = atoi(aux);
	close (fd);	
  return 1;
}


int pintaErrorArg(){
	write(1, ARG_, strlen(ARG_));
	return 0;
}

int pintaErrorFitxer(){
	write(1, EFITX_, strlen(EFITX_));
	return 0;
}
