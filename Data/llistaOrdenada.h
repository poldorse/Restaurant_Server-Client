#ifndef _LLISTA_ORDENADA_H_
#define _LLISTA_ORDENADA_H_

#include "dataFunc.h"

typedef struct c {
	Enterprise ent;
	struct c* seg;
} NodeC;

typedef struct {
	NodeC* cap;
	NodeC* ant;
} LlistaOrdenada;

LlistaOrdenada PDI_crea ();
int PDI_insereixEntOrd (LlistaOrdenada* l, Enterprise e);
Enterprise PDI_consulta (LlistaOrdenada l);
int PDI_esborra (LlistaOrdenada* l);
int PDI_avanca (LlistaOrdenada* l);
int PDI_vesInici (LlistaOrdenada* l);
int PDI_vesFinal (LlistaOrdenada* l);
int PDI_fi (LlistaOrdenada l);
int PDI_buida (LlistaOrdenada l);
int PDI_destrueix (LlistaOrdenada* l);

#endif
