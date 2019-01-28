#include "trama.h"



int prepararIEnviarTrama(Trama trama, int fd){
  char * buffer;
  //unsigned int iactual = 0;
  unsigned int auxLength, j, w;
  unsigned char auxLengthH, auxLengthL;
  int length, i, flag;
  bzero(&buffer, sizeof(buffer));
	  i = 0;
  //preparem la infomació per enviar-la segons el tipus de transmisio que volem fer
	  buffer = malloc(sizeof(char));	
      buffer[i] = trama.type;
	  flag=write(fd, &buffer[i], sizeof(char));
	  if(flag<0) tancar_prog();
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
	  flag=write(fd, &buffer[i], sizeof(char));
	  if(flag<0) tancar_prog();
	  i++;
	  buffer = realloc(buffer, (i+1)*sizeof(char));	  
	  buffer[i] =  auxLengthL;
	  write(fd, &buffer[i], sizeof(char));
	  i++;
	  j = 0;
	  buffer = realloc(buffer, (i+1)*sizeof(char));
	  for(j = 0; trama.data[j]!= '\0'; j++){
		buffer[i] = trama.data[j];
		//write(fd, &buffer[i], sizeof(char));
		buffer = realloc(buffer, (i+1)*sizeof(char));
		i++;		
	  }
	  flag=write(fd, trama.data, strlen(trama.data));
	  if(flag<0) tancar_prog();
	return 1;
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

Trama ompleTrama(int tipus, DadesPicard dades){
	int i = 0, len = 0, j, k,primeraLletra =1;
	Trama trama;
	char aux[20];
	char auxc;
	char *plat;
	switch (tipus){
		case 0:
			//envia el seu  nom a data per registrar-se
			trama.type = '1';
			strcpy(trama.header, "PIC_NAME");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			while(dades.nomClient[len]!='\n'){				
				len++;
			}
			len--;
			trama.data = malloc(sizeof(char));
			for(i = 0;i<len;i++){
				trama.data[i] = dades.nomClient[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			trama.data[i] = '\0';
			break;	
		case 1:
			//envia el seu nom i diners per registrar-se a un enterprise
			trama.type='1';
			strcpy(trama.header, "PIC_INF");						
			for (i=0;i<3;i++){
				trama.header[7+i]='\0';				
			}
			while(dades.nomClient[len]!='\n'){				
				len++;			
			}
			len--;
			trama.data=malloc(sizeof(char));
			for(i = 0;i<len;i++){
				trama.data[i] = dades.nomClient[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			trama.data[i] = '&';
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			len=sprintf(aux, "%d", dades.calers);
			for(j=0;j<len;j++){
				trama.data[i] = aux[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i] = '\0';
			break;	
		case 2:
			trama.type = '3';
			strcpy(trama.header, "SHW_MENU");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;	
		case 3:
			read(0, &auxc, sizeof(char));
			while(auxc == ' ') read(0, &auxc, sizeof(char));
			len=0;
			aux[0] = '\0';
			while(auxc >= '0' && auxc <='9'){
				if (len >18) {
					trama.data = malloc(sizeof(char));
					trama.data[0]='\0';
					return trama;
				}
				aux[len] = auxc;
				len++;
				read(0, &auxc, sizeof(char));
			}
			primeraLletra = 1;
			i=0;
			plat = malloc(sizeof(char));
			while(auxc == ' ') read(0, &auxc, sizeof(char));
			while (auxc != '\n' ) {	
				if(auxc == ' '){
					plat[i] = auxc;
					i++;
					plat = realloc(plat, sizeof(char)*(i+1));				
					while(auxc == ' ') read(0, &auxc, sizeof(char));
				}
				if((auxc >= 'a' && auxc <= 'z')|| (auxc >= 'A' && auxc <= 'Z')){
					if((primeraLletra)&&(auxc >= 'a' && auxc <= 'z')) auxc -= 'a' - 'A';
					if((!primeraLletra)&&(auxc >= 'A' && auxc <= 'Z')) auxc += 'a' -'A';
					primeraLletra=0;
					plat[i] = auxc;
					i++;
					plat = realloc(plat, sizeof(char)*(i+1));	
				}	
				read(0, &auxc, sizeof(char));
			}
			plat[i] = '\n';
			trama.type = '4';
			strcpy(trama.header, "NEW_ORD");
			for (k=0;k<3;k++){
				trama.header[7+k]='\0';				
			}
			trama.data = malloc(sizeof(char));
			for(k=0;k<i;k++){
				trama.data[k] = plat[k];
				trama.data = realloc(trama.data, (k+2)*sizeof(char));
			}
			trama.data[k] = '&';
			// free(plat);
			k++;
			trama.data = realloc(trama.data, (k+1)*sizeof(char));
			for(j=0;j<len;j++){
				trama.data[k+j] =aux[j];
				trama.data = realloc(trama.data, (k+j+2)*sizeof(char));
			}
			trama.data[k+j]= '\0';	
			break;
		case 4:
			read(0, &auxc, sizeof(char));
			while(auxc == ' ') read(0, &auxc, sizeof(char));
			len=0;
			aux[0] = '\0';
			while(auxc >= '0' && auxc <='9'){
				if (len >18) {
					trama.data = malloc(sizeof(char));
					trama.data[0]='\0';
					return trama;
				}
				aux[len] = auxc;
				len++;
				read(0, &auxc, sizeof(char));
			}
			primeraLletra = 1;
			i=0;
			plat = malloc(sizeof(char));
			while(auxc == ' ') read(0, &auxc, sizeof(char));
			while (auxc != '\n' ) {	
				if(auxc == ' '){
					plat[i] = auxc;
					i++;
					plat = realloc(plat, sizeof(char)*(i+1));				
					while(auxc == ' ') read(0, &auxc, sizeof(char));
				}
				if((auxc >= 'a' && auxc <= 'z')|| (auxc >= 'A' && auxc <= 'Z')){
					if((primeraLletra)&&(auxc >= 'a' && auxc <= 'z')) auxc -= 'a' - 'A';
					if((!primeraLletra)&&(auxc >= 'A' && auxc <= 'Z')) auxc += 'a' -'A';
					primeraLletra=0;
					plat[i] = auxc;
					i++;
					plat = realloc(plat, sizeof(char)*(i+1));	
				}	
				read(0, &auxc, sizeof(char));
			}
			plat[i] = '\n';
			trama.type = '5';
			strcpy(trama.header, "DEL_ORD");
			for (k=0;k<3;k++){
				trama.header[7+k]='\0';				
			}
			trama.data = malloc(sizeof(char));
			for(k=0;k<i;k++){
				trama.data[k] = plat[k];
				trama.data = realloc(trama.data, (k+2)*sizeof(char));
			}
			trama.data[k] = '&';
			// free(plat);
			k++;
			trama.data = realloc(trama.data, (k+1)*sizeof(char));
			for(j=0;j<len;j++){
				trama.data[k+j] =aux[j];
				trama.data = realloc(trama.data, (k+j+2)*sizeof(char));
			}
			trama.data[k+j]= '\0';	
			break;
		case 5:
			trama.type = '2';
			strcpy(trama.header, "PIC_NAME");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			len=0;
			while(dades.nomClient[len]!='\n'){				
				len++;	
			}
			len--;
			trama.data=malloc(sizeof(char));
			for(i = 0;i<len;i++){
				trama.data[i] = dades.nomClient[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
			}
			trama.data[i]='\0';
			break;
		case 6:
			trama.type = '6';
			strcpy(trama.header, "PAY");
			for (i=0;i<7;i++){
				trama.header[3+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
	}	
	return trama;
}

int alliberaTrama(Trama* trama){
	free(trama->data);
	return 1;
}

int analitzaTrama(Trama trama){
	switch (trama.type){
		case '0':
			if(!strcmp(trama.header, "ENT_INF")) return 15; //quan es desconnecta el servidor
			break;
		case '1':
			if(!strcmp(trama.header, "ENT_INF")) return 1; //quan data dona un enterprise correcte a picard
			if(!strcmp(trama.header, "CONKO")) return 2; //quan no s'ha pogut assignar enterprise a data i quan la connexio amb enterprise es incompatible
			if(!strcmp(trama.header, "CONOK")) return 3; //quan picard no s'ha pogut connectar a enterprise
			break;
		case '2':
			if(!strcmp(trama.header, "CONOK")) return 4; //quan picard s'ha pogut desconnectar correctament de enterprise
			if(!strcmp(trama.header, "CONKO")) return 5; //quan picard no s'ha pogut desconnectar correctament de enterprise
			break;
		case '3':
			if(!strcmp(trama.header, "DISH")) return 6;  //quan enterprise envia un plat correctament a picard
			if(!strcmp(trama.header, "END_MENU")) return 7;  //quan enterprise ja ha acabat d'enviar el menu a picard
			break;
		case '4':
			if(!strcmp(trama.header, "ORDOK")) return 8;  //quan picard ha estat possible processar una comanda
			if(!strcmp(trama.header, "ORDKO")) return 9;  //quan picard no ha estat possible processar una comanda
			break;
		case '5':
			if(!strcmp(trama.header, "ORDOK")) return 10;  //quan picard ha estat possible eliminar una comanda
			if(!strcmp(trama.header, "ORDKO")) return 11;  //quan picard no ha estat possible eliminar una comanda
			break;
		case '6':
			if(!strcmp(trama.header, "PAYOK")) return 12;  //quan picard ha estat possible pagar el procediment
			if(!strcmp(trama.header, "PAYKO")) return 13;  //quan picard no ha estat possible de pagar una comanda
			break;
		default: 
			return 0;
	}
	return 0;	
}

int guardaEnterprise(DadesPicard* dades, Trama trama){
	int i= 0,j;
	char aux[20];
	while(trama.data[i]!='&'){
		i++;
	}
	i++;
	aux[0]='\0';
	j=0;
	while(trama.data[i]!='&'){
		aux[j]=trama.data[i];
		j++;
		i++;
	}
	i++;
	aux[j]='\0';
	dades->port=atoi(aux);
	j=0;
	dades->ip[0]='\0';
	while(trama.data[i]!='\0'){
		dades->ip[j]=trama.data[i];
		i++;
		j++;
	}
	return 1;
}

int printaPlat(Trama trama){
	int i= 0;
	while(trama.data[i]!='&'){
		write(1,&trama.data[i], sizeof(char));
		i++;
	}
	i++;
	write(1, " (", strlen(" ("));
	while(trama.data[i]!='&'){
		write(1,&trama.data[i], sizeof(char));
		i++;
	}
	write(1, " euros) \n", strlen(" euros) \n"));
	return 1;
}

void tancar_prog(){
	if(connectat){
		Trama trama;
		trama = ompleTrama(5, dades);
		prepararIEnviarTrama(trama, fd2);
		alliberaTrama(&trama);
		trama=rebTrama(fd2);
		alliberaTrama(&trama);
	}
    if (fd > 0) close(fd);
	if (fd2 >0) close(fd2);
	write(1, SORTIR_, strlen(SORTIR_));
	raise(SIGKILL);
}