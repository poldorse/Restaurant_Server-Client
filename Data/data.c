#include "dataFunc.h"
#include "thread.h"
#include "connexio.h"
#include "trama.h"
#include "llistaOrdenada.h"


LlistaOrdenada enterprises;
pthread_mutex_t mutexEnterprises = PTHREAD_MUTEX_INITIALIZER;

int main (){	
	//declaracio variables
	Dades dades;
	Trama trama;
	enterprises = PDI_crea();
	int sockent, fdSocket, quinatrama, nument = -1, entOK=0, entACT = 0, entDESC = 0;
	pthread_t thpic;
	Enterprise enterprise;
	//error al llegir fitxer de configuracio
	if(!obtDades(&dades)){
		write(1, EFITX_, strlen(EFITX_));
		exit(EXIT_FAILURE);
	}
	//crea thread per picards, ja que poden rebre picards i enterprises a l'hora
	pthread_create(&thpic, NULL, threadPerPicards, &dades);
	//configuracio socket per enterprises
	fdSocket = configSocketEnt(dades);
	while(1){
		//acceptarem socket
		sockent=acceptarSocket(fdSocket);
		//error al acceptar el socket
		if (sockent < 1) {
			write(1, ERR_CON_SAL, strlen( ERR_CON_SAL));
			exit(EXIT_FAILURE);
		}
		//reb la trama
		trama = rebTrama(sockent);
		//analitza la trama per decidir quin tipus de buffer ha d'enviar de retorn
		quinatrama=analitzaTrama(trama);
		switch(quinatrama){
			case 0:
				//la trama es erronia		
				break;
			case 2:
				pthread_mutex_lock(&mutexEnterprises);
				nument++;
				//guarda un enterprise correctament
				entOK=afegirEnterprise(trama);
				if(entOK==1){
					//guarda correctament el enterprise
					alliberaTrama(&trama);
					trama=ompleTrama(0,enterprise);	
					prepararIEnviarTrama(trama, sockent);
				}else{
					//guarda un enterprise amb error
					trama=ompleTrama(1,enterprise);
					prepararIEnviarTrama(trama, sockent);
				}
				pthread_mutex_unlock(&mutexEnterprises);
				break;
			case 3:
				//un enterprise es vol desconectar
				pthread_mutex_lock(&mutexEnterprises);
				entDESC=desconectarEnterprise(trama);
				if(entDESC==1){
					//ha desconectat correctament l'enterprise
					trama=ompleTrama(4,enterprise);
					prepararIEnviarTrama(trama,sockent);
					close(sockent);
				}else{
					//NO ha desconectat correctament l'enterprise
					trama=ompleTrama(5,enterprise);
					prepararIEnviarTrama(trama,sockent);
				}	
				pthread_mutex_unlock(&mutexEnterprises);
				break;
			case 4:
				//volem actualitzar el nombre de picards al enterprise
				pthread_mutex_lock(&mutexEnterprises);
				entACT=actualitzarEnterprise(trama);
				if(entACT == 1){
					//s'ha actualitzat el nombre de picards al enterprise correctament
					trama=ompleTrama(2,enterprise);
					prepararIEnviarTrama(trama,sockent);
				}else{
					//NO s'ha actualitzat correctament el nombre de picards al enterprise
					trama=ompleTrama(3,enterprise);
					prepararIEnviarTrama(trama,sockent);
				}
				pthread_mutex_unlock(&mutexEnterprises);
				break;
		}
		close(sockent);
	}	
	return 0;
}
