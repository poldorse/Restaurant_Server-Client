#ifndef FUNCIONS_H
#define FUNCIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define SORTIR_ "\n\nEl Enterprise es desconnecta..\n\n "
#define SORTIR_KO "\n\nEl Enterprise no s'ha pogut desconnectar correctament..\n\n "
#define ARG_ "Falten arguments\n"
#define COM_ "introdueixi comandes:\n"
#define EFITX_ "Error al llegir fitxer.\n"
#define PRINT_ "\n\n[Comanda OK]\n\n"
#define PRINT_0 "[Comanda KO]\n\n"
#define ERR_C  "Error al intentar conectar el socket.\n"
#define ACTOK "\n[ACTUALITZACIO OK]\n"
#define ACTKO "\n[ACTUALITZACIO KO]\n"


typedef struct{
	char *nomRestaurant;
	int segons;
	char ipdata[20];
	int portdata;
	char ippicard[20];
	int portpicard;
	int numPicards;
} DadesConfigEnterprise;

typedef struct{
	char *NomPlat;
	int nPlats;
	int preuPlat;
}Plat;


int pintaErrorArg();
int pintaErrorFitxer();
int obtDadesEnterprise(DadesConfigEnterprise *dades, char nomF[20]);

	

#endif
