/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab2/client.c
 * @author Avinal Kumar
 * @since February 03, 2021
 *
 * LAB 2 - Computer Networks
 * Client program to send file
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#define PORT 2047

int main()
{
    int sock1;
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;

    //struct sockaddr_in client;
    memset(&serv, 0, sizeof(serv));

    serv.sin_port = htons(PORT);
    //printf("%x %x\n",PORT,htons(PORT));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Client connecting...\n");
    connect(sock1, (struct sockaddr *)&serv, sizeof(serv));
    char buf[50];
    FILE *fp = fopen("client.txt", "r");
    printf("Preparing file...\n");
    while (!feof(fp))
    {
        fread(buf, sizeof(char), 50, fp);
        write(sock1, buf, 50);
        //bzero(buf,sizeof(buf));
    }
    write(sock1, "complete", 50);
    sleep(2);
    printf("File Successfully sent to Server\n");
    sleep(4);
    fclose(fp);
    return 0;
}