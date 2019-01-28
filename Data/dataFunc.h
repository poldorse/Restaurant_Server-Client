#ifndef DATAFUNC_H
#define DATAFUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


#include <time.h>


#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>




#define EFITX_ "Error al llegir fitxer.\n"
#define ERR_C  "Error al intentar conectar el socket.\n"
#define ERR_CR_S "ERROR: creacion de socket\n"
#define ERR_B "ERROR: bind\n"
#define ESP_    "Esperando nueva conexion... \n"
#define ERR_A "Error accept\n"
#define NUE "connectado\n"
#define	ERR_CON_SAL "Error al hacer connexión"


typedef struct{

	char ip[20];
	int portPicard;
	int portEnterprise;

} Dades;

typedef struct{
	char *nomRestaurant;
	int numpicards;
	char ipent[20];
	int portent;
} Enterprise;

int obtDades(Dades *dades);
int printar(char *frase);



#endif
