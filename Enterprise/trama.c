#include "trama.h"


Trama ompleTrama(int tipus, DadesConfigEnterprise infoConfigEnter, Plat plat, int diners){
	unsigned int i = 0, len, j;
	Trama trama;
	char buffer[20];	
	switch (tipus){
		//un picard es connecta correctament
		case 0:   
			trama.type = '1';
			strcpy(trama.header, "CONOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//un picard no es connecta correctament
		case 2:
			trama.type = '1';
			strcpy(trama.header, "CONKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		case 1:
			trama.type = '1';
			strcpy(trama.header, "ENT_INF");
			for (i=0;i<3;i++){
				trama.header[7+i]='\0';				
			}			
			trama.data = malloc(sizeof(char));
			len= 0;
			for(i=0; infoConfigEnter.nomRestaurant[i] != '\0';i++) len++;
			len--;
			for(i=0;i<len; i++){
				trama.data[i] = infoConfigEnter.nomRestaurant[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			trama.data[i] = '&';	
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			len = sprintf(buffer, "%d", infoConfigEnter.portpicard);
			for(j = 0; j<len;j++){
				trama.data[i] = buffer[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '&';	
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			len = sprintf(buffer, "%s", infoConfigEnter.ipdata);
			for(j = 0; j<len;j++){
				trama.data[i] = buffer[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '\0';
			break;
		case 3:
			trama.type = '3';
			strcpy(trama.header, "DISH");
			for (i=0;i<6;i++){
				trama.header[4+i]='\0';				
			}			
			trama.data = malloc(sizeof(char));
			len= 0;
			for(i=0; plat.NomPlat[i] != '\n';i++) len++;
			len--;
			for(i=0;i<len; i++){
				trama.data[i] = plat.NomPlat[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			trama.data[i] = '&';	
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			len = sprintf(buffer, "%d", plat.preuPlat);
			for(j = 0; j<len;j++){
				trama.data[i] = buffer[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '&';	
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			len = sprintf(buffer, "%d", plat.nPlats);
			for(j = 0; j<len;j++){
				trama.data[i] = buffer[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '\0';
			break;
		case 4:
			trama.type = '3';
			strcpy(trama.header, "END_MENU");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//ha pogut fer comanda satisfactoriament
		case 5:
			trama.type = '4';
			strcpy(trama.header, "ORDOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//no ha pogut fer comanda
		case 6:
			trama.type = '4';
			strcpy(trama.header, "ORDKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//ha pogut eliminar un plat correctament
		case 7:
			trama.type = '5';
			strcpy(trama.header, "ORDOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//no ha pogut eliminar un plat
		case 8:
			trama.type = '5';
			strcpy(trama.header, "ORDKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//un picard es desconnecta correctament
		case 9:   
			trama.type = '2';
			strcpy(trama.header, "CONOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//un picard no es desconnecta correctament
		case 10:
			trama.type = '2';
			strcpy(trama.header, "CONKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		case 11:
		//pagament OK
			trama.type = '6';
			strcpy(trama.header, "PAYOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			i=0;
			len=sprintf(buffer, "%d", diners);
			for(i=0;i<len;i++){
				trama.data[i] = buffer[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '\0';
			break;
		case 12:
		//pagament KO
			trama.type = '6';
			strcpy(trama.header, "PAYKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
	}	
	return trama;
}

Trama rebTrama(int fd){	
	unsigned char auxLengthH, auxLengthL;
	char aux;
	//int i = 0;
	unsigned int auxLength, w;
	int i;
	Trama trama;
	trama.data = NULL;	
	read(fd, &aux, sizeof(char));
	trama.type = aux;
	for(i = 0; i < 10; i++){
		read(fd, &aux, sizeof(char));
		trama.header[i] = aux;
	}
	read(fd, &auxLengthH, sizeof(char));
	read(fd, &auxLengthL, sizeof(char));
	auxLength = 0xFF & auxLengthH;
	auxLength = (auxLength << 8) & 0xFF00;
	auxLength = auxLength | auxLengthL;
	trama.length=auxLength;
	//trama.data = malloc(sizeof(char));
	//read(fd, &aux, sizeof(char));
	i = 0;
	trama.data = malloc(sizeof(char));
	if(auxLength!=0){
		for (w = 0; w<auxLength ; w++){
			if(w!=0){
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			read(fd, &aux, sizeof(char));
			trama.data[i] = aux;
			i++;		
		}
	}
	trama.data[i] = '\0';
	return trama;	
}

int prepararIEnviarTrama(Trama trama, int fd){
  char * buffer;
  //unsigned int iactual = 0;
  unsigned int auxLength, j;
  unsigned char auxLengthH, auxLengthL;
  unsigned int w;
  int length, i;
  bzero(&buffer, sizeof(buffer));
	  i = 0;
  //preparem la infomació per enviar-la segons el tipus de transmisio que volem fer
	  buffer = malloc(sizeof(char));	
      buffer[i] = trama.type;
	  write(fd, &buffer[i], sizeof(char));
      i++;
	  buffer = realloc(buffer, (i+1)*sizeof(char));	
	  
      for(j=0; j < 10; j++){
        buffer[i] =  trama.header[j];	
		write(fd, &buffer[i], sizeof(char));		
		buffer = realloc(buffer, (i+1)*sizeof(char));
        i++;
      }	  
	  length = 0;	
	  auxLength = 0x0000;									
	  for(j = 0; trama.data[j]!= '\0'; j++){
		  length++;
	  }
		length++;									
	  for(w = 0; w<j ; w++){
		  auxLength = auxLength + 1;
	  }		   
	  auxLengthL = 0xFF & auxLength;
	  auxLengthH = 0xFF & (auxLength>>8);
	   buffer[i] =  auxLengthH;	
	   write(fd, &buffer[i], sizeof(char));
	   i++;
	  buffer = realloc(buffer, (i+1)*sizeof(char));	  
	  buffer[i] =  auxLengthL;
	  write(fd, &buffer[i], sizeof(char));
	  i++;
	  j = 0;
	  buffer = realloc(buffer, (i+1)*sizeof(char));
	  for(j = 0; trama.data[j]!= '\0'; j++){
		buffer[i] = trama.data[j];
		buffer = realloc(buffer, (i+1)*sizeof(char));
		i++;		
	  }
	  write(fd, trama.data, strlen(trama.data));
	return 1;
}

int alliberaTrama(Trama* trama){
	free(trama->data);
	return 1;
}

int analitzaTrama(Trama trama){
	switch (trama.type){
		case '1':
			if(!strcmp(trama.header, "PIC_INF")) return 1; //rep un picard correctament, li envia el seu nom i els diners
			if(!strcmp(trama.header, "CONKO")) return 2; //quan enterprise no s'ha pogut registrar a Data
			if(!strcmp(trama.header, "CONOK")) return 3; //quan enterprise s'ha pogut registrar a Data
			break;
		case '2':
			if(!strcmp(trama.header, "PIC_NAME")) return 4; //quan enterprise rep una trama de desconnexio de picard
			if(!strcmp(trama.header, "CONOK")) return 5; //quan enterprise s'ha pogut desconnectar correctament de data
			if(!strcmp(trama.header, "CONKO")) return 6; //quan enterprise no s'ha pogut desconnectar correctament de data
			break;
		case '3':
			if(!strcmp(trama.header, "SHW_MENU")) return 7;  //quan picard envia a enterprise que vol mostrar el seu menu
		case '4':
			if(!strcmp(trama.header, "NEW_ORD")) return 8;  //quan picard vol demanar una nova comanda
		case '5':
			if(!strcmp(trama.header, "DEL_ORD")) return 9;  //quan picard vol eliminar una comanda
		case '6':
			if(!strcmp(trama.header, "PAY")) return 10;  //quan picard vol processar el pagament
		case '7':
			if(!strcmp(trama.header, "UPDATEOK")) return 11;  //quan s'ha actualitzat a data correctament
			if(!strcmp(trama.header, "UPDATEKO")) return 12;  //quan no s'ha actualitzat a data correctament
		default: 
			return 0;
	}
	return 0;	
}

Trama ompleTramaPerActualitzar(){
	Trama trama;
	int i,j, len=0;
	char buffer[20];
	buffer[0]='\0';
	trama.type = '7';
	strcpy(trama.header, "UPDATE");
	for (i=0;i<4;i++){
		trama.header[6+i]='\0';				
	}
	trama.data = malloc(sizeof(char));
	len = sprintf(buffer, "%d", infoConfigEnter.portpicard);
	for(i = 0; i<len;i++){
		trama.data[i] = buffer[i];
		trama.data = realloc(trama.data, (i+1)*sizeof(char));
	}
	trama.data[i] = '&';
	trama.data = realloc(trama.data, (i+1)*sizeof(char));
	i++;
	len = sprintf(buffer, "%d", infoConfigEnter.numPicards);
	for(j = 0; j<len;j++){
		trama.data[i] = buffer[j];
		trama.data = realloc(trama.data, (i+1)*sizeof(char));
		i++;
	}
	trama.data[i]='\0';	
	return trama;	
}

int guardaSaldoPicard(Trama trama){
	int saldo = 0, i=0,j=0;
	char aux[20];
	aux[0]='\0';
	while(trama.data[i]!='&') i++;
	i++;
	while(trama.data[i]!='\0'){
		aux[j]=trama.data[i];
		i++;
		j++;
	}
	aux[j]='\0';
	saldo=atoi(aux);
	return saldo;
}

void actualitzaPicards(){	
	int fdd;
	//configurem el socket per parlar amb data
	fdd = CSocketAmbData(infoConfigEnter);
	//error de socket amb data
	if (fdd < 1) {
		write(1, ERR_C, strlen(ERR_C));
		exit(EXIT_FAILURE);
	}
	Trama trama = ompleTramaPerActualitzar();	
	prepararIEnviarTrama(trama, fdd);
	alliberaTrama(&trama);
	trama = rebTrama(fdd);
	if(analitzaTrama(trama)==11){
		write(1, ACTOK, strlen(ACTOK));
	}else{
		write(1, ACTKO, strlen(ACTKO));
	}
	//declarem un altre cop la alarma
	alarm(infoConfigEnter.segons);	
}

void tancar_prog(){
    Trama trama;
	int fdd, i, len= 0, j;
	char buffer[20];
	buffer[0] = '\0';
	//configurem el socket per parlar amb data
	fdd = CSocketAmbData(infoConfigEnter);
	//error de socket amb data
	if (fdd < 1) {
		write(1, ERR_C, strlen(ERR_C));
		exit(EXIT_FAILURE);
	}
	trama.type = '2';
	strcpy(trama.header, "ENT_INF");
	for (i=0;i<3;i++){
		trama.header[7+i]='\0';				
	}			
	trama.data = malloc(sizeof(char));
	len = sprintf(buffer, "%d", infoConfigEnter.portpicard);
	for(i = 0; i<len;i++){
		trama.data[i] = buffer[i];
		trama.data = realloc(trama.data, (i+1)*sizeof(char));
	}
	trama.data[i] = '\0';
	prepararIEnviarTrama(trama, fdd);
	alliberaTrama(&trama);
	trama = rebTrama(fdd);
	if(analitzaTrama(trama)==5){
		write(1, SORTIR_, strlen(SORTIR_));		
	}else{
		write(1, SORTIR_KO, strlen(SORTIR_KO));
	}
	for (j=0; j<cont;j++){
		trama.type = '0';
		strcpy(trama.header, "ENT_INF");
		for (i=0;i<3;i++){
			trama.header[7+i]='\0';
		}					
		trama.data = malloc(sizeof(char));
		trama.data[0] = '\0';
		prepararIEnviarTrama(trama, sockpic[j]);
		alliberaTrama(&trama);
		close(sockpic[j]);
	}
	if (fd2 > 0) close(fd2);
	if (fd > 0) close (fd);
	free(thpic);
	PDI_destrueix(&plats);
	close(fdd);
	raise(SIGKILL);
}
	