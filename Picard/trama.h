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
#include <errno.h>

#include "fitxer.h"

extern int fd, fd2, connectat;
extern DadesPicard dades;

typedef struct{
  char type;
  char header[10];
  unsigned int length;
  char *data;
}Trama;

int prepararIEnviarTrama(Trama trama, int fd);
Trama ompleTrama(int tipus, DadesPicard dades);
Trama rebTrama(int fd);
int analitzaTrama(Trama trama);
void tancar_prog();
int alliberaTrama(Trama* trama);
int guardaEnterprise(DadesPicard* dades, Trama trama);
int printaPlat(Trama trama);

#endif