#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/*By Luis Alvarez*/
int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char* mensaje;
    
    if(argc ==2 ){
        mensaje = argv[1];
    }else{
        perror("Numero incorrecto de argumentos.");
        exit(1);
    }
/*  Create a socket for the client.  */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
/*  Name the socket, as agreed with the server.  */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 3004;
    len = sizeof(address);

 
/*  Now connect our socket to the server's socket.  */
    result = connect(sockfd, (struct sockaddr *)&address, len);
 
    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }
 
/*  We can now read/write via sockfd.  */
    char res[30];
    write(sockfd, mensaje, 50);
    read(sockfd, &res, 30);
    printf("Servidor: %s\n", res);
    close(sockfd);
    return 0;

}
