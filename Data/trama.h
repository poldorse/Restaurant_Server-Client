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

#include "dataFunc.h"
#include "llistaOrdenada.h"

extern LlistaOrdenada enterprises;

typedef struct{
  char type;
  char header[10];
  unsigned int length;
  char *data;
}Trama;

Trama rebTrama(int fd);
int analitzaTrama(Trama trama);
int prepararIEnviarTrama(Trama trama, int fd);
Trama ompleTrama(int tipus, Enterprise enterprise);
int afegirEnterprise(Trama trama);
int actualitzarEnterprise(Trama trama);
int desconectarEnterprise(Trama trama);
int alliberaTrama(Trama* trama);

#endif
