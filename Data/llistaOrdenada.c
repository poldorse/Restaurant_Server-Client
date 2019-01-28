#include "llistaOrdenada.h"

LlistaOrdenada PDI_crea () {
	LlistaOrdenada ll;
	ll.cap = (NodeC*) malloc (sizeof (NodeC) );	
	if (ll.cap == NULL) {
		return ll;
	}else{
		ll.ant = ll.cap;
		ll.ant->seg = NULL;
	}
	return ll;
}
int PDI_insereixEntOrd (LlistaOrdenada* l, Enterprise e) {
	NodeC* aux;
	aux=(NodeC*)malloc(sizeof(NodeC));	
	if(aux==NULL){
		return 0;
	}else{
		l->ant = l->cap;
		while(l->ant->seg != NULL && e.numpicards > l->ant->seg->ent.numpicards){
			l->ant = l->ant->seg;
		}
		aux->ent = e;
		aux->seg = l->ant->seg;
		l->ant->seg = aux;
		l->ant = aux;
	}
	return 1;
}
Enterprise PDI_consulta (LlistaOrdenada l) {
	Enterprise e;
	e.nomRestaurant = NULL;
	e.numpicards = -1;
	e.ipent[0] = '\0';
	e.portent = -1;
	if (l.ant->seg != NULL) {
		e = l.ant->seg->ent;
	}
	return e;
}
int PDI_esborra (LlistaOrdenada* l) {
	NodeC* aux;
	if (l->ant->seg != NULL) {
		aux = l->ant->seg;
		l->ant->seg = aux->seg;
		free (aux);
	}else{
		return 0;
	}
	return 1;
}
int PDI_avanca (LlistaOrdenada* l) {	
	if (l->ant->seg == NULL) {
		return 0;
	}else{
		l->ant = l->ant->seg;
	}
	return 1;
}
int PDI_vesInici (LlistaOrdenada* l) {	
	l->ant = l->cap;
	return 1;
}
int PDI_vesFinal (LlistaOrdenada* l) {
	l->ant = l->cap;
	while (l->ant->seg != NULL) {
		l->ant = l->ant->seg;
	}
	return 1;
}
int PDI_fi (LlistaOrdenada l) {	
	return l.ant->seg == NULL;
}
int PDI_buida (LlistaOrdenada l) {	
	return l.cap->seg == NULL;
}
int PDI_destrueix (LlistaOrdenada* l) {
	NodeC* aux;
	l->ant = NULL;
	while (l->cap != NULL) {
		aux = l->cap;
		l->cap = aux->seg;
		free (aux);
	}
	return 1;
}

