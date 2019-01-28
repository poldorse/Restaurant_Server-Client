#include "thread.h"


void * threadPerPicards(void* arg){
	Dades dades = *(Dades*)arg;
	int fdSocket,sockpic;
	Trama trama;
	Enterprise ent;
	//configura socket picard
	fdSocket = configSocketPic(dades);
	while (1){
		//acceptarem socket
		sockpic = acceptarSocket(fdSocket);
		//mira error de socket de picard
		if (sockpic <  1 ) {
			write(1, ERR_CON_SAL, strlen( ERR_CON_SAL));
			exit(EXIT_FAILURE);
		}
		//reb trama
		trama = rebTrama(sockpic);
		if(PDI_buida (enterprises)){
			//la llista de enterprises esta buida per tant, no pot asignar cap enterprise
			trama=ompleTrama(6, ent);
			prepararIEnviarTrama(trama, sockpic);
		}else{
			pthread_mutex_lock(&mutexEnterprises);
			//assigna un enterprise al picard
			PDI_vesInici (&enterprises);
			ent = PDI_consulta (enterprises);
			PDI_esborra (&enterprises);
			ent.numpicards++;
			PDI_insereixEntOrd (&enterprises, ent);
			trama=ompleTrama(7, ent);
			prepararIEnviarTrama(trama, sockpic);
			pthread_mutex_unlock(&mutexEnterprises);
		}		
	}
	close(sockpic);
	return NULL;
}

