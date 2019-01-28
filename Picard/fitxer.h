#ifndef FITXER_H
#define FITXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>


#define SORTIR_ "\n\nGràcies per fer servir LsEat. Fins la propera. \n\nTanquem i sortim\n "
#define ARG_ "Falten arguments\n"
#define COM_ "introdueixi comandes:\n"
#define EFITX_ "Error al llegir fitxer.\n"
#define PRINT_ "\n\n[Comanda OK]\n\n"
#define PRINT_COMOK "\nEl plat s'ha afegit correctament.\n"
#define PRINT_COMKO "\nEl plat no s'ha afegit correctament.\n"
#define PRINT_COMEOK "\nEl plat s'ha eliminar correctament.\n"
#define PRINT_COMEKO "\nEl plat no s'ha eliminar correctament.\n"
#define PRINT_0 "\n[Comanda KO]\n"
#define ERR_C  "Error al intentar conectar el socket.\n"
#define ERR_CON_ENT "No s'ha pogut connectar amb un enterprise.\n"
#define PRINT_DESOK "El Picard s'ha desconnectat correctament.\n"
#define PRINT_DESKO "El Picard no ha pogut desconectar-se correctament.\n"
#define PRINT_PAYOK "S'ha finalitzat el pagament correctament.\n"
#define PRINT_PAYKO "No s'ha pogut finalitzar el pagament correctament.\n"

typedef struct{

	char *nomClient;
	int sizeNom;
	int calers;
	char ip[20];
	int port;

}DadesPicard;

typedef struct{
	char *plat;
	int nPlats;

}Plats;


char* DemanaComanda(int escriu, DadesPicard dades);
int pintaInfo(DadesPicard dades);
int pintaErrorFitxer();
int pintaErrorArg();
int obtDades(DadesPicard *dades, char nomF[20]);
int printar(char *frase);

#endif
