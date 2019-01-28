#include "connexio.h"

int CSocketAmbData(DadesConfigEnterprise dades){
	char aux[20];
    int client_socket;
    client_socket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(client_socket < 0){
        sprintf(aux, "error creacio del socket\n");
		write(1, aux, strlen(aux));
		exit(-1);
    }
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(dades.portdata);
    s_addr.sin_addr.s_addr = inet_addr(dades.ipdata);
   if (connect(client_socket, (void *)&s_addr, sizeof(s_addr))<0){
	  sprintf(aux, "error de connexio\n");
	  write(1, aux, strlen(aux));
      close(client_socket);
      exit(-1);
    }
    return client_socket;
}


int CSocketAmbPicard(DadesConfigEnterprise dades){
    struct sockaddr_in s_addr;
    int fdSocket = -1;
	fdSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(fdSocket<0){
      write(1, ERR_CR_S, strlen(ERR_CR_S));
      return -1;
    }
	memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(dades.portpicard);
    s_addr.sin_addr.s_addr =inet_addr(dades.ippicard);
    if(bind(fdSocket, (void *)&s_addr, sizeof(s_addr))<0){
			write(1, ERR_B, strlen(ERR_B));
      return -1;
    }
    return fdSocket;
}

int acceptarSocket( int fdSocket){
	struct sockaddr_in cliente_addr;
	listen(fdSocket,128);
	socklen_t cliente_len = sizeof(cliente_addr);
	write(1, ESP_, strlen(ESP_));
    int sock = accept(fdSocket, (void *)&cliente_addr, &cliente_len);
    if(sock < 0){
	  write(1, ERR_A, strlen(ERR_A));
      return -1;
    }
    return sock;
}