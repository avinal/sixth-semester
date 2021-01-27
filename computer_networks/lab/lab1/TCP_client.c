/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab1/TCP_client.c
 * @author Avinal Kumar
 * @since January 27, 2021
 * Roll Number - 185067
 *
 * LAB 1
*/

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2047 // Q1: previously 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "TCP Client: Hello this message has been changed. Did you get it?";
    char buffer[4096] = {0}; // Q4: changed to 4096
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Q3: changed to localhost

    // Convert IPv4 and IPv6 addresses from text to binary form
    // This binds the client to localhost
    /*if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} */

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("New message sent\n");
    valread = read(sock, buffer, 4096); // Q4: changed to 4096
    printf("%s\n", buffer);
    return 0;
}
