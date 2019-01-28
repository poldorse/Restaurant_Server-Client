#ifndef CONNEXIO_H
#define CONNEXIO_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
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

#include "dataFunc.h"

int configSocketPic(Dades dades);
int configSocketEnt(Dades dades);
int acceptarSocket( int fdSocket);


#endif