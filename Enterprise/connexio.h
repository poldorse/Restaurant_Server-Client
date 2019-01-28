#ifndef CONNEXIO_H
#define CONNEXIO_H

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


#include "funcions.h"



#define EFITX_ "Error al llegir fitxer.\n"
#define ERR_C  "Error al intentar conectar el socket.\n"
#define ERR_CR_S "ERROR: creacion de socket\n"
#define ERR_B "ERROR: bind\n"
#define ESP_    "Esperando nueva conexion... \n"
#define ERR_A "Error accept\n"
#define NUE "connectado\n"
#define	ERR_CON_SAL "Error al hacer connexión"



int CSocketAmbData(DadesConfigEnterprise dades);
int CSocketAmbPicard(DadesConfigEnterprise dades);
int acceptarSocket( int fdSocket);


#endif