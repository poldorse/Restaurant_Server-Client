#include "connexio.h"

int CSocket(DadesPicard dades){

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
    s_addr.sin_port = htons(dades.port);
    s_addr.sin_addr.s_addr = inet_addr(dades.ip);

   if (connect(client_socket, (void *)&s_addr, sizeof(s_addr))<0){

	  sprintf(aux, "error de connexio\n");
	  write(1, aux, strlen(aux));
      close(client_socket);
      exit(-1);
    }

    return client_socket;
}
