#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/*By Luis Alvarez*/
int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    /*  Create an unnamed socket for the server.  */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /*  Name the socket.  */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 3004;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    /*  Create a connection queue and wait for clients.  */
    listen(server_sockfd, 5);
    while (1)
    {
        char mensaje[50];
        struct sockaddr_storage addr;
        char ipstr[INET6_ADDRSTRLEN];
        char *response = "Respuesta recibida";

        /*  Accept a connection.  */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
                               (struct sockaddr *)&client_address, &client_len);

        /*  We can now read/write to client on client_sockfd.  */
        inet_ntop(AF_INET, &client_address.sin_addr, ipstr, sizeof ipstr);
        read(client_sockfd, &mensaje, 50);
        printf("%s: %s\n", ipstr, mensaje);
        // msg = "Recibido";
        write(client_sockfd, response, 30);
        close(client_sockfd);
    }
}
