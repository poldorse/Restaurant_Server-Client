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


#include "fitxer.h"



#define EFITX_ "Error al llegir fitxer.\n"
#define ERR_C  "Error al intentar conectar el socket.\n"


int CSocket(DadesPicard dades);


#endif
