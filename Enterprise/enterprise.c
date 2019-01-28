#include "funcions.h"
#include "connexio.h"
#include "trama.h"
#include "thread.h"
#include "llista.h"


Llista plats;
DadesConfigEnterprise infoConfigEnter;
pthread_t *thpic;
int fd2, fd, cont;
int* sockpic;

int main (int argc, char *argv[]){	
	char nomF_Config[20];
	char nomF_Menu[20];	
	plats = PDI_crea();
	Plat plat;	
	Trama trama;	
	infoConfigEnter.numPicards = 0;
	cont=0;
	thpic = malloc(sizeof(pthread_t));
	sockpic = malloc(sizeof(int));
	infoConfigEnter.numPicards=0;
	signal(SIGINT, tancar_prog);
	//declarem signal alarma actualitza
	signal(SIGALRM, actualitzaPicards);
	//prova de error de arguments
	if(argc != 3){
		pintaErrorArg();
		exit(EXIT_FAILURE);
	}	
	strcpy(nomF_Config, argv[1]);	
	if(!obtDadesEnterprise(&infoConfigEnter, nomF_Config)){
		pintaErrorFitxer();
		exit(EXIT_FAILURE);
	}	
	strcpy(nomF_Menu, argv[2]);
	//guardem les dades en el menu
	if(!obtDadesMenu(nomF_Menu)){
		pintaErrorFitxer();
		exit(EXIT_FAILURE);
	}
	strcpy(nomF_Menu, argv[2]);
	//configurem el socket per parlar amb data
	fd = CSocketAmbData(infoConfigEnter);
	//error de socket amb data
	if (fd < 1) {
		write(1, ERR_C, strlen(ERR_C));
		exit(EXIT_FAILURE);
	}
	//enviem solicitud de nou enterprise amb data per registrar-nos
	trama = ompleTrama(1, infoConfigEnter, plat, fd);	
	prepararIEnviarTrama(trama, fd);
	//alliberem i rebem si ha sigut possible el registre a data
	alliberaTrama(&trama);
	trama = rebTrama(fd);
	if(analitzaTrama(trama)==2) return 0;
	//tanquem socket
	close(fd);
	//declarem cada quan salta la interrupcio de actualitzar
	alarm(infoConfigEnter.segons);
	//obrim connexio amb picard
	fd2 = CSocketAmbPicard(infoConfigEnter);
	//error de declaracio de port
	if (fd < 1) {
		write(1, ERR_C, strlen(ERR_C));
		exit(EXIT_FAILURE);
	}
	while(1){
		//acceptem picards
		sockpic[cont]=acceptarSocket(fd2);
		if (sockpic[cont] < 1) {
			write(1, ERR_CON_SAL, strlen( ERR_CON_SAL));
			exit(EXIT_FAILURE);
		}
		if(infoConfigEnter.numPicards>0) thpic = realloc( thpic, (infoConfigEnter.numPicards+1)*sizeof(pthread_t));
		pthread_create(&thpic[infoConfigEnter.numPicards], NULL, threadPerPicards, &sockpic[cont]);
		cont++;
		sockpic = realloc(sockpic, (cont+1)*sizeof(int));
	}
	return 0;	
}
