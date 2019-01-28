#include "llista.h"

Llista PDI_crea () {
	Llista ll;
	ll.cap = (NodeC*) malloc (sizeof (NodeC) );	
	if (ll.cap == NULL) {
		return ll;
	}else{
		ll.ant = ll.cap;
		ll.ant->seg = NULL;
	}
	return ll;
}
int PDI_insereix (Llista* l, Plat plat) {
	NodeC* aux;
	aux=(NodeC*)malloc(sizeof(NodeC));	
	if(aux==NULL){
		return 0;
	}else{
		l->ant = l->cap;
		while(l->ant->seg != NULL){
			l->ant = l->ant->seg;
		}
		aux->plat = plat;
		aux->seg = l->ant->seg;
		l->ant->seg = aux;
		l->ant = aux;
	}
	return 1;
}
Plat PDI_consulta (Llista l) {
	Plat p;
	if (l.ant->seg != NULL) {
		p = l.ant->seg->plat;
	}
	return p;
}
int PDI_esborra (Llista* l) {
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
int PDI_avanca (Llista* l) {	
	if (l->ant->seg == NULL) {
		return 0;
	}else{
		l->ant = l->ant->seg;
	}
	return 1;
}
int PDI_vesInici (Llista* l) {	
	l->ant = l->cap;
	return 1;
}
int PDI_vesFinal (Llista* l) {
	l->ant = l->cap;
	while (l->ant->seg != NULL) {
		l->ant = l->ant->seg;
	}
	return 1;
}
int PDI_fi (Llista l) {	
	return l.ant->seg == NULL;
}
int PDI_buida (Llista l) {	
	return l.cap->seg == NULL;
}
int PDI_destrueix (Llista* l) {
	NodeC* aux;
	l->ant = NULL;
	while (l->cap != NULL) {
		aux = l->cap;
		l->cap = aux->seg;
		free (aux);
	}
	return 1;
}

//guardem les dades del menu en una llista
int obtDadesMenu(char nomF_Menu[20]){
	Plat plat;
	int count = 0, error = 0;  
	long int resF = -1;
	char aux_char = '\0', aux[20];
	aux[0] = '\0';
	int fdM = -1;
	fdM = open(nomF_Menu, O_RDONLY);
	if (fdM <= 0) return 0;
	resF = read(fdM, &aux_char, 1);
	while(aux_char!='\n' && resF>0){
		plat.NomPlat = malloc(sizeof(char));
		while (aux_char != '\n') {
			plat.NomPlat[count] = aux_char;
			plat.NomPlat = realloc(plat.NomPlat, (count+1)*sizeof(char));
			resF = read(fdM, &aux_char, 1);
			count++;
		}
		plat.NomPlat[count] = '\n';
		count = 0;
		resF = read(fdM, &aux_char, 1);
		while (aux_char != '\n') {
			aux[count] = aux_char;
			resF = read(fdM, &aux_char, 1);
			count++;
		}
		plat.nPlats = atoi(aux);
		aux[0] = '\0';
		count = 0;
		resF = read(fdM, &aux_char, 1);  
		while (aux_char != '\n') {
			aux[count] = aux_char;
			resF = read(fdM, &aux_char, 1);
			count++;
		}
		plat.preuPlat = atoi(aux);
		aux[0] = '\0';
		count = 0;
		resF = read(fdM, &aux_char, 1);
		error=PDI_insereix (&plats,plat);
		if(!error) {	
			close(fdM);
			return 0;
		}				
	}
	close (fdM);
	return 1;
}




