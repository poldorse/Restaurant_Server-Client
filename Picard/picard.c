
#include "fitxer.h"
#include "connexio.h"
#include "trama.h"

int fd, fd2,connectat=0;
DadesPicard dades;

int main (int argc, char *argv[]){
	char nomF[20];
	int final = 0;
	Trama trama;
	signal(SIGINT, tancar_prog);
	if(argc != 2){
		pintaErrorArg();
		exit(EXIT_FAILURE);
	}
	strcpy(nomF, argv[1]);
	if(!obtDades(&dades, nomF)){
		pintaErrorFitxer();
		exit(EXIT_FAILURE);
	}
	pintaInfo(dades);
	while (!final) {
        if (!strcmp(DemanaComanda(1, dades), "DESCONNECTA") && connectat==1) {
			//envia trama per notificar desconexio
			trama = ompleTrama(5, dades);
			prepararIEnviarTrama(trama, fd2);
			alliberaTrama(&trama);
			//rep resposta
			trama = rebTrama(fd2);
			if(analitzaTrama(trama)==15) tancar_prog();
			if(analitzaTrama(trama)==4){
				//rep desconexio OK
				write(1, PRINT_DESOK, strlen(PRINT_DESOK));
				final = 1;
				connectat =0;
			}else{
				//rep desconexio KO
				write(1, PRINT_DESKO, strlen(PRINT_DESKO));
			}
			alliberaTrama(&trama);			
        }else{
			if(!strcmp(DemanaComanda(0, dades), "PAGAR") && connectat ==1){
				//envia voler pagar
				write(1, PRINT_, strlen(PRINT_));
				trama = ompleTrama(6, dades);
				prepararIEnviarTrama(trama, fd2);
				alliberaTrama(&trama);
				// rep resposta
				trama = rebTrama(fd2);
				if(analitzaTrama(trama)==15) tancar_prog();
				if(analitzaTrama(trama)==12){
					//rep pagar comandes OK
					write(1, PRINT_PAYOK, strlen(PRINT_PAYOK));
				}else{
					//rep pagar comandes KO
					write(1, PRINT_PAYKO, strlen(PRINT_PAYKO));
				}
			}else{
				if(!strcmp(DemanaComanda(0, dades), "DEMANA") && connectat==1){
					//envia voler un plat
				    write(1, PRINT_, strlen(PRINT_));
					trama = ompleTrama(3, dades);
					prepararIEnviarTrama(trama, fd2);
					alliberaTrama(&trama);
					// rep resposta
					trama = rebTrama(fd2);
					if(analitzaTrama(trama)==15) tancar_prog();
					if(analitzaTrama(trama)==8){
						//rep comanda plat OK
						write(1, PRINT_COMOK, strlen(PRINT_COMOK));
					}else{
						//rep comanda plat KO
						write(1, PRINT_COMKO, strlen(PRINT_COMKO));
					}
					alliberaTrama(&trama);
				}else{
					if(!strcmp(DemanaComanda(0, dades), "ELIMINA") && connectat==1){
						//envia eliminar comanda
						write(1, PRINT_, strlen(PRINT_));
						trama = ompleTrama(4, dades);
						prepararIEnviarTrama(trama, fd2);
						alliberaTrama(&trama);
						// rep resposta
						trama = rebTrama(fd2);
						if(analitzaTrama(trama)==15) tancar_prog();
						if(analitzaTrama(trama)==10){
							//rep comanda eliminar plat OK
							write(1, PRINT_COMEOK, strlen(PRINT_COMOK));
						}else{
							//rep comanda eliminar plat KO
							write(1, PRINT_COMEKO, strlen(PRINT_COMKO));
						}	
						alliberaTrama(&trama);						
					}else{
						if(!strcmp(DemanaComanda(0, dades), "MOSTRA MENU") && connectat==1){
							write(1, PRINT_, strlen(PRINT_));
							//enviem que volem mostrar menu
							trama = ompleTrama(2, dades);
							prepararIEnviarTrama(trama, fd2);
							alliberaTrama(&trama);
							//rebem menu
							write(1, "\nMENU DISPONIBLE:\n", strlen("\nMENU DISPONIBLE:\n"));
							trama = rebTrama(fd2);
							if(analitzaTrama(trama)==15) tancar_prog();
							while (analitzaTrama(trama)==6){
								printaPlat(trama);
								alliberaTrama(&trama);
								trama=rebTrama(fd2);
							}
							alliberaTrama(&trama);			
								
						}else{
							if(!strcmp(DemanaComanda(0, dades), "CONNECTA")&& connectat==0){
									//connectem picard a data
									fd = CSocket(dades);
									if (fd < 1) {
										write(1, ERR_C, strlen(ERR_C));
										exit(EXIT_FAILURE);
									}
									write(1, PRINT_, strlen(PRINT_));
									//enviem solicitud de enterprise
									trama = ompleTrama(0, dades);
									prepararIEnviarTrama(trama, fd);
									alliberaTrama(&trama);
									trama=rebTrama(fd);
									if(analitzaTrama(trama)==15) tancar_prog();
									//tanquem connexio amb Data, ja no hi entrarem més
									close(fd);
									switch(analitzaTrama(trama)){
										//reb conectament un enterprise
										case 1:
											guardaEnterprise(&dades, trama);
											//connectem picard a enterprise
											fd2 = CSocket(dades);
											if(fd2<1){
												write(1, ERR_C, strlen(ERR_C));
												exit(EXIT_FAILURE);
											}
											connectat=1;
											break;
										case 2:
											write(1, ERR_CON_ENT, strlen(ERR_CON_ENT));
											exit(EXIT_FAILURE);
											break;
										default:
											exit(EXIT_FAILURE);
									}
									//envia trama amb nom picard i calers a enterprise
									trama=ompleTrama(1, dades);
									prepararIEnviarTrama(trama,fd2);
									alliberaTrama(&trama);	
									//rep si s'ha guardat correctament la seva configuració
									trama=rebTrama(fd2);
									if(analitzaTrama(trama)==15) tancar_prog();
									if(analitzaTrama(trama)==2){
										exit(EXIT_FAILURE);
									}	
							}else{
								write(1, PRINT_0, strlen(PRINT_0));
							}
						}
					}
				}
			}
		}
	}
	tancar_prog();
	return 0;
}
