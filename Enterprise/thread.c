#include "thread.h"

pthread_mutex_t mutexPicards = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexLlista = PTHREAD_MUTEX_INITIALIZER;

void * threadPerPicards(void* arg){
	Trama trama;
	int fd2 = *(int*)arg;
	int saldo=0, i,j, numUnits, trobat, preuComanda=0, flag=0, flag2=0;
	int volDesconectar = 0;
	Plat plat, auxPlat;
	char aux[20];
	DadesConfigEnterprise ent;
	char* NomPlat;
	Llista platsComanda = PDI_crea();
	pthread_mutex_lock(&mutexPicards);
	infoConfigEnter.numPicards++;
	pthread_mutex_unlock(&mutexPicards);
	write(1,"S'ha connectat un Picard.\n", strlen("S'ha connectat un Picard.\n"));
	//rebem el picard amb els diners
	trama=rebTrama(fd2);
	saldo=guardaSaldoPicard(trama);
	alliberaTrama(&trama);
	if(saldo<0){
		//configuracio KO
		trama=ompleTrama(2,ent,plat, preuComanda);
		prepararIEnviarTrama(trama, fd2);
		return NULL;		
	}
	//configuracio OK
	trama=ompleTrama(0, ent, plat, preuComanda);
	prepararIEnviarTrama(trama, fd2);
	alliberaTrama(&trama);	
	while(!volDesconectar){
		trama=rebTrama(fd2);
		switch(analitzaTrama(trama)){
			case 7:
			pthread_mutex_lock(&mutexLlista);
				//Envia el menu al picard
				PDI_vesInici (&plats);
				//envia plat a plat
				while(!PDI_fi (plats)){
					plat = PDI_consulta (plats);
					trama=ompleTrama(3,ent,plat, preuComanda);
					prepararIEnviarTrama(trama,fd2);
					alliberaTrama(&trama);
					PDI_avanca (&plats);
				}
				//envia fi menu
				trama=ompleTrama(4,ent,plat, preuComanda);
				prepararIEnviarTrama(trama,fd2);
				alliberaTrama(&trama);
				pthread_mutex_unlock(&mutexLlista);
				break;
			case 8:
				pthread_mutex_lock(&mutexLlista);
				//rep un comanda de picard
				aux[0]='\0';
				NomPlat = malloc(sizeof(char));
				i= 0;
				//guarda el plat
				while(trama.data[i]!='&'){
					NomPlat[i]=trama.data[i];
					i++;
					NomPlat=realloc(NomPlat, (i+1)*sizeof(char));
				}
				i++;
				NomPlat[i]='\0';
				j=0;
				//guarda units que vol el client
				while(trama.data[i]!='\0'){
					aux[j]=trama.data[i];
					i++;
					j++;
				}
				aux[j]='\0';
				numUnits=atoi(aux);
				//busca si plat coincideix
				PDI_vesInici (&plats);
				trobat = 0;
				flag = 0;
				while(!PDI_fi (plats)&&trobat==0){
					if(flag) PDI_avanca (&plats);
					flag = 1;
					plat = PDI_consulta (plats);
					j=0;
					while(plat.NomPlat[j]!='\n') j++;
					plat.NomPlat[j-1] = '\0';
					//el plat esta en la llista
					if(!strcmp(plat.NomPlat, NomPlat)){
						//el restaurant te suficient unitats
						if(numUnits <= plat.nPlats){
							plat = PDI_consulta (plats);
							trama=ompleTrama(5,ent,plat,preuComanda);
							PDI_esborra(&plats);
							plat.nPlats = plat.nPlats - numUnits;
							//el guarda a una llista de plats demanats
							if (plat.nPlats != 0) PDI_insereix (&plats, plat);
							plat.nPlats = numUnits;
							flag2=0;
							PDI_vesInici(&platsComanda);
							if (PDI_buida(platsComanda)){
								flag2 = 1;
								PDI_insereix(&platsComanda, plat);
							}
							while(flag2==0 && !PDI_fi (platsComanda)){
								auxPlat=PDI_consulta(platsComanda);
								if(!strcmp(auxPlat.NomPlat, plat.NomPlat)){
									flag2=1;
									PDI_esborra(&platsComanda);
									auxPlat.nPlats = auxPlat.nPlats+plat.nPlats; 
									PDI_insereix(&platsComanda, auxPlat);
								}
								PDI_avanca(&platsComanda);								
							}
							if(flag2==0) PDI_insereix(&platsComanda, plat);
						}else{ //el restaurant no te suficients unitats
							trama=ompleTrama(6,ent,plat,preuComanda);
						}
						trobat=1;
					}	
					
				}
				//si no ha trobat el plat
				if (trobat==0) trama=ompleTrama(6,ent,plat,preuComanda);
				//enviem resultat
				prepararIEnviarTrama(trama,fd2);
				alliberaTrama(&trama);
				free(NomPlat);
				/*
				PDI_vesInici(&platsComanda);
				while(!PDI_fi(platsComanda)){
					auxPlat =PDI_consulta(platsComanda);
					PDI_avanca(&platsComanda);
				}*/
				pthread_mutex_unlock(&mutexLlista);
				break;
			case 9:
				pthread_mutex_lock(&mutexLlista);
				//rep un elimina comanda de picard
				aux[0]='\0';
				NomPlat = malloc(sizeof(char));
				i= 0;
				//guarda el plat
				while(trama.data[i]!='&'){
					NomPlat[i]=trama.data[i];
					i++;
					NomPlat=realloc(NomPlat, (i+1)*sizeof(char));
				}
				i++;
				NomPlat[i]='\0';
				j=0;
				//guarda units que vol el client
				while(trama.data[i]!='\0'){
					aux[j]=trama.data[i];
					i++;
					j++;
				}
				aux[j]='\0';
				numUnits=atoi(aux);
				//busca si plat coincideix
				PDI_vesInici (&platsComanda);
				trobat = 0;
				flag = 0;
				while(!PDI_fi (platsComanda)&&trobat==0){
					if(flag) PDI_avanca (&platsComanda);
					flag = 1;
					plat = PDI_consulta (platsComanda);
					j=0;
					while(plat.NomPlat[j]!='\n') j++;
					plat.NomPlat[j-1] = '\0';
					//el plat esta en la llista
					if(!strcmp(plat.NomPlat, NomPlat)){
						//el restaurant te suficient unitats
						if(numUnits <= plat.nPlats){
							plat = PDI_consulta (platsComanda);
							trama=ompleTrama(7,ent,plat,preuComanda);
							PDI_esborra(&platsComanda);
							plat.nPlats = plat.nPlats - numUnits;
							//el guarda a una llista de plats demanats
							if (plat.nPlats != 0) PDI_insereix (&platsComanda, plat);
							plat.nPlats = numUnits;
							flag2=0;
							PDI_vesInici(&plats);
							if (PDI_buida(plats)){
								flag2 = 1;
								PDI_insereix(&plats, plat);
							}
							while(flag2==0 && !PDI_fi (plats)){
								auxPlat=PDI_consulta(plats);
								if(!strcmp(auxPlat.NomPlat, plat.NomPlat)){
									flag2=1;
									PDI_esborra(&plats);
									auxPlat.nPlats = auxPlat.nPlats+plat.nPlats; 
									PDI_insereix(&plats, auxPlat);
								}
								PDI_avanca(&plats);								
							}
							if(flag2==0) PDI_insereix(&plats, plat);
						}else{ //el restaurant no te suficients unitats
							trama=ompleTrama(8,ent,plat,preuComanda);
						}
						trobat=1;
					}	
					
				}
				//si no ha trobat el plat
				if (trobat==0) trama=ompleTrama(8,ent,plat,preuComanda);
				//enviem resultat
				prepararIEnviarTrama(trama,fd2);
				alliberaTrama(&trama);
				free(NomPlat);
				/*
				PDI_vesInici(&platsComanda);
				while(!PDI_fi(platsComanda)){
					auxPlat =PDI_consulta(platsComanda);
					PDI_avanca(&platsComanda);
				}*/
				pthread_mutex_unlock(&mutexLlista);
				break;
			case 4://un picard es vol desconectar
				//tornarem a posar els plats a la llista
				pthread_mutex_lock(&mutexLlista);
				flag=PDI_buida(platsComanda);
				if(!flag){
					flag2=0;
					PDI_vesInici(&platsComanda);
					while(!flag2){
						if (PDI_fi(platsComanda)){
							flag2=1;
						}else{
							auxPlat =PDI_consulta(platsComanda);
							PDI_vesInici(&plats);
							trobat=0;
							while(!PDI_fi(plats)&&!trobat){
								plat=PDI_consulta(plats);
								if(!strcmp(auxPlat.NomPlat, plat.NomPlat)){
									trobat=1;
									PDI_esborra(&plats);
									plat.nPlats= plat.nPlats+auxPlat.nPlats;
									PDI_insereix(&plats, plat);									
								}	
								PDI_avanca(&plats);
							}
							if (!trobat) PDI_insereix(&plats, auxPlat);
							PDI_avanca(&platsComanda);
						}
					}
					//destruim la llista, ja que el client al final no demanara
					flag2 = PDI_destrueix(&platsComanda);					
				}else{
					flag2=1;
				}
				if (!flag2){
					trama=ompleTrama(10,ent,plat,preuComanda);
				}else{
					trama=ompleTrama(9,ent,plat,preuComanda);
				}
				prepararIEnviarTrama(trama,fd2);
				alliberaTrama(&trama);
				pthread_mutex_lock(&mutexPicards);
				infoConfigEnter.numPicards--;
				pthread_mutex_unlock(&mutexPicards);
				//tanquem socket
				close(fd2);
				volDesconectar=1;
				pthread_mutex_unlock(&mutexLlista);
				write(1, "Picard desconnectat..", strlen("Picard desconnectat.."));
				return NULL;
				break;
			case 10:
			//el picard vol tramitar el pagament
				preuComanda=0;
				PDI_vesInici(&platsComanda);
				flag2=0;
				if(!PDI_buida(platsComanda)){
					while(!flag2){
						auxPlat =PDI_consulta(platsComanda);
						if (PDI_fi(platsComanda)) flag2=1;
						if(!flag2) preuComanda = preuComanda + auxPlat.preuPlat* auxPlat.nPlats;
						PDI_avanca(&platsComanda);
					}
				}
				//enviem resposta
				if(preuComanda<=saldo && !PDI_buida(platsComanda)){
					trama=ompleTrama(11,ent,plat,preuComanda);
					PDI_destrueix(&platsComanda);
					saldo = saldo -preuComanda;
					platsComanda= PDI_crea();
				}else{
					trama=ompleTrama(12,ent,plat,preuComanda);
				}
				prepararIEnviarTrama(trama,fd2);
				alliberaTrama(&trama);
				break;
		}
		
	}
	return NULL;
}

