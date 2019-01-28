#include "trama.h"

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

int analitzaTrama(Trama trama){
	switch (trama.type){
		case '1':
			if(!strcmp(trama.header, "PIC_NAME")) return 1; //quan un picard demana un enterprise 
			if(!strcmp(trama.header, "ENT_INF")) return 2; //quan es vol registrar un enterprise
			break;
		case '2':
			if(!strcmp(trama.header, "ENT_INF")) return 3; //quan un enterprise es vol desconectar
			break;
		case '7':
			if(!strcmp(trama.header, "UPDATE")) return 4;  //quan un enterprise vol actualitzar el numero de picards
			break;
		default: 
			return 0;
	}
	return 0;	
}

int prepararIEnviarTrama(Trama trama, int fd){
  char * buffer;
  unsigned int auxLength, j;
  unsigned char auxLengthH, auxLengthL;
  unsigned int  w;
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
Trama ompleTrama(int tipus, Enterprise enterprise){
	unsigned int i = 0, j = 0;
	Trama trama;
	char aux[20];
	aux[0]='\0';
	switch (tipus){
		//guarda un enterprise correctament
		case 0:   
			trama.type = '1';
			strcpy(trama.header, "CONOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//guarda un enterprise amb error
		case 1:
			trama.type = '1';
			strcpy(trama.header, "CONKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//actualitza correctament un enterprise
		case 2:
			trama.type = '7';
			strcpy(trama.header, "UPDATEOK");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//no actualitza correctament un enterprise
		case 3:
			trama.type = '7';
			strcpy(trama.header, "UPDATEKO");
			for (i=0;i<2;i++){
				trama.header[8+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		case 4:   
		//el enterprise s'ha desconectat correctament
			trama.type = '2';
			strcpy(trama.header, "CONOK");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//el enterprise NO s'ha desconectat correctament
		case 5:
			trama.type = '2';
			strcpy(trama.header, "CONKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//data no pot assignar a picard cap enterprise perque no hi ha cap de conectat
		case 6:
			trama.type = '1';
			strcpy(trama.header, "CONKO");
			for (i=0;i<5;i++){
				trama.header[5+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			trama.data[0]='\0';
			break;
		//data asigna un enterprise a un picard
		case 7:
			trama.type = '1';
			strcpy(trama.header, "ENT_INF");
			for (i=0;i<3;i++){
				trama.header[7+i]='\0';				
			}
			trama.data = malloc(sizeof(char));
			for(i=0; i<strlen(enterprise.nomRestaurant);i++){
				trama.data[i] = enterprise.nomRestaurant[i];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));			
			}
			trama.data[i]= '&';
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			sprintf(aux, "%d", enterprise.portent);
			for(j=0; j<4;j++){
				trama.data[i] = aux[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
			}
			trama.data[i]= '&';
			trama.data = realloc(trama.data, (i+1)*sizeof(char));
			i++;
			j=0;
			while(enterprise.ipent[j]){
				trama.data[i]=enterprise.ipent[j];
				trama.data = realloc(trama.data, (i+1)*sizeof(char));
				i++;
				j++;				
			}
			trama.data[i]='\0';
			break;
	}		
	return trama;
}

int afegirEnterprise(Trama trama){
	int i = 0, j = 0;
	char aux[20];
	Enterprise enterprise;
	enterprise.nomRestaurant = malloc(sizeof(char));
	while(trama.data[i]!='&'){
		enterprise.nomRestaurant[i] = trama.data[i];
		i++;
		enterprise.nomRestaurant = realloc(enterprise.nomRestaurant, (i+1)*sizeof(char));
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
	enterprise.portent=atoi(aux);
	j=0;
	while(trama.data[i]!='\0'){
		enterprise.ipent[j]=trama.data[i];
		i++;
		j++;
	}
	enterprise.ipent[j]='\0';
	enterprise.numpicards=0;
	PDI_insereixEntOrd (&enterprises, enterprise);
	return 1;
}


int actualitzarEnterprise(Trama trama){
	int port, i, j, numpic= 0;
	char aux[20];
	i = 0;
	Enterprise ent;
	ent.numpicards=0;
	aux[0]='\0';
	while(trama.data[i]!='&'){
		aux[i]= trama.data[i];
		i++;
	}
	aux[i]='\0';
	port= atoi(aux);
	i++;
	aux[0]='\0';
	j=0;
	while(trama.data[i]!='\0'){
		aux[j]=trama.data[i];
		i++;
		j++;
	}
	aux[j]='\0';
	numpic=atoi(aux);
	PDI_vesInici(&enterprises);
	while(!PDI_fi(enterprises)){
		ent = PDI_consulta (enterprises);
		if(ent.portent == port){
			PDI_esborra (&enterprises);
			ent.numpicards=numpic;
			PDI_insereixEntOrd (&enterprises, ent);
			return 1;
		}
		PDI_avanca(&enterprises);
	}
	return 0;
}

int desconectarEnterprise(Trama trama){
	int port, i;
	char aux[20];
	i = 0;
	Enterprise ent;
	aux[0]='\0';
	while(trama.data[i]!='\0'){
		aux[i]= trama.data[i];
		i++;
	}
	aux[i]='\0';
	port= atoi(aux);
	PDI_vesInici (&enterprises);
	while(!PDI_fi(enterprises)){
		ent = PDI_consulta (enterprises);
		if(ent.portent == port){
			PDI_esborra (&enterprises);
			return 1;			
		}
		PDI_insereixEntOrd (&enterprises, ent);
		PDI_avanca(&enterprises);
	}	
	return 0;
}

int alliberaTrama(Trama* trama){
	free(trama->data);
	return 1;
}
