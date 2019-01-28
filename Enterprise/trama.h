#ifndef TRAMA_H
#define TRAMA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "funcions.h"
#include "connexio.h"
#include "llista.h"


extern DadesConfigEnterprise infoConfigEnter;
extern int fd2, fd, cont;
extern pthread_t *thpic;
extern Llista plats;
extern int* sockpic;

typedef struct{
  char type;
  char header[10];
  unsigned int length;
  char* data;
}Trama;

int prepararIEnviarTrama(Trama trama, int fd);
Trama ompleTrama(int tipus, DadesConfigEnterprise infoConfigEnte, Plat plat, int diners);
Trama rebTrama(int fd);
int alliberaTrama(Trama* trama);
int analitzaTrama(Trama trama);
int guardaSaldoPicard(Trama trama);
void actualitzaPicards();
void tancar_prog();

#endif
