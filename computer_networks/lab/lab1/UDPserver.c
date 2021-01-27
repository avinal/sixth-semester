/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab1/UDPserver.c
 * @author Avinal Kumar
 * @since January 27, 2021
 * Roll Number - 185067
 *
 * LAB 1 
*/

// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 2047    // Q1: previously 8080
#define MAXLINE 4096 // Q4: changed to 4096

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "UDP Server: Yeah we've got the new message.";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;                     // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Q3: changed to loacalhost
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    printf("Processing ...!!!\n");
    sleep(4);

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("New message sent.\n");

    return 0;
}
