/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab1/TCP_server.c
 * @author Avinal Kumar
 * @since January 27, 2021
 * Roll Number - 185067
 *
 * LAB 1 
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2047 // Q1: previously 8080

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[4096] = {0}; // Q4: changed to 4096
    char *hello = "TCP Server: Yeah we've got the new message.";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    /*if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}*/
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Q4: chenged to localhost
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 7) < 0) // Q2: listen(server_fd, 3)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 4096); // Q4: changed to 4096
    printf("%s\n", buffer);
    printf("Processing ...!!!\n");
    sleep(4);
    send(new_socket, hello, strlen(hello), 0);
    printf("New message sent\n");
    return 0;
}
