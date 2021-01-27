/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab1/UDPclient.c
 * @author Avinal Kumar
 * @since January 27, 2021
 * Roll Number - 185067
 *
 * LAB 1
*/

// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 2047	 // Q1: previously 8080
#define MAXLINE 4096 // Q4: changed to 4096

// Driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "UDP Client: Hello this message has been changed. Did you get it?";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Q3: changed to localhost

	int n, len;

	sendto(sockfd, (const char *)hello, strlen(hello),
		   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));
	printf("New message sent.\n");

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				 MSG_WAITALL, (struct sockaddr *)&servaddr,
				 &len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);

	close(sockfd);
	return 0;
}