#ifndef _LLISTA_ORDENADA_H_
#define _LLISTA_ORDENADA_H_

#include "funcions.h"

typedef struct c {
	Plat plat;
	struct c* seg;
} NodeC;

typedef struct {
	NodeC* cap;
	NodeC* ant;
}Llista;

extern Llista plats;

Llista PDI_crea ();
int PDI_insereix (Llista* l, Plat plat);
Plat PDI_consulta (Llista l);
int PDI_esborra (Llista* l);
int PDI_avanca (Llista* l);
int PDI_vesInici (Llista* l);
int PDI_vesFinal (Llista* l);
int PDI_fi (Llista l);
int PDI_buida (Llista l);
int PDI_destrueix (Llista* l);
int obtDadesMenu(char nomF_Menu[20]);

#endif
