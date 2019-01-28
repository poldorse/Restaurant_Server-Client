#include "fitxer.h"

int fd = -1;
char *comanda, *auxp, *auxString;

int obtDades(DadesPicard *dades, char nomF[20]){
	int count = 0;
    long res = -1;
    char aux_char = '\0', aux_calers[20], aux_port[20];
    fd = open(nomF, O_RDONLY);
    if (fd <= 0) return 0;
	dades->nomClient = NULL;
	dades->nomClient = malloc(sizeof(char));
	res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
		dades->nomClient[count] = aux_char;
		dades->nomClient = realloc(dades->nomClient, (count+1)*sizeof(char));
		res = read(fd, &aux_char, 1);
		count++;
    }
		dades->sizeNom = count-1;
	dades->nomClient[count] = '\n';
    count = 0;
	res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        aux_calers[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }
	dades->calers = atoi(aux_calers);
    count = 0;
    res = read(fd, &aux_char, 1);
    while (aux_char != '\n') {
        dades->ip[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }
	dades->ip[count-1]='\0';
	count = 0;
    res = read(fd, &aux_char, 1);
    while (res != 0 || aux_char != '\n') {
        aux_port[count] = aux_char;
        res = read(fd, &aux_char, 1);
        count++;
    }
    dades->port = atoi(aux_port);
	close (fd);
  return 1;
}

char* DemanaComanda(int escriu, DadesPicard dades){
	int count = 0;
	char aux, nomC[100];
	int para = 0;
	switch (escriu){
			case 0:
				return comanda;
				break;
			case 1:
				para = 0;
				count = 0;
				comanda = NULL;
				printar("\n");
				sprintf(nomC, "%s->", dades.nomClient);
				write(1,nomC, strlen(nomC));
				comanda = malloc(sizeof(char));
				while (aux != '\n' ) {
					read(0, &aux, sizeof(char));
					if(aux >= 'a' && aux <= 'z' && !para){
						aux -= 'a' - 'A';
					}
					comanda[count] = aux;
					count++;
					comanda = realloc(comanda, sizeof(char)*(count+1));
					comanda[count] = '\0';

					if(!strcmp(comanda, "DEMANA")) return "DEMANA";
					if(!strcmp(comanda, "ELIMINA")) return "ELIMINA";
				}
				aux = '\0';
				comanda[count-1] = '\0';
				return comanda;
				break;
	}
	return "error";
}

int pintaInfo(DadesPicard dades){
	char auxString[100];
	sprintf(auxString, "Benvingut %s",dades.nomClient);
	write(1, auxString, strlen(auxString));
	sprintf(auxString, "Té %d Euros disponibles. \n",dades.calers);
	write(1, auxString, strlen(auxString));
   write(1, COM_, strlen(COM_));
	return 0;
}

int pintaErrorArg(){
	write(1, ARG_, strlen(ARG_));
	return 0;
}

int pintaErrorFitxer(){
	write(1, EFITX_, strlen(EFITX_));
	return 0;
}

int printar(char *frase){
	write(1,frase,strlen(frase));
	return 1;
}
