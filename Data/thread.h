#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


#include "trama.h"
#include "dataFunc.h"
#include "llistaOrdenada.h"
#include "connexio.h"


extern LlistaOrdenada enterprises;
extern pthread_mutex_t mutexEnterprises;

void * threadPerPicards(void* dades);


#endif