#include "connexio.h"

int configSocketPic(Dades dades){
    struct sockaddr_in s_addr;
    int fdSocket = -1;
	fdSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(fdSocket<0){
      write(1, ERR_CR_S, strlen(ERR_CR_S));
      return -1;
    }
	memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(dades.portPicard);
    s_addr.sin_addr.s_addr =inet_addr(dades.ip);
    if(bind(fdSocket, (void *)&s_addr, sizeof(s_addr))<0){
		write(1, ERR_B, strlen(ERR_B));
		return -1;
    }
    return fdSocket;
}
int configSocketEnt(Dades dades){
    struct sockaddr_in s_addr;
    int fdSocket = -1;
	fdSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(fdSocket<0){
      write(1, ERR_CR_S, strlen(ERR_CR_S));
      return -1;
    }
	memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(dades.portEnterprise);
    s_addr.sin_addr.s_addr =inet_addr(dades.ip);
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
    write(1, NUE, strlen(NUE));
    return sock;
}