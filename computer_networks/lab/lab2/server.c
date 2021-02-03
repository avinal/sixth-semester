/**
 * /mnt/z/my_git/sixth-semester/computer_networks/simulation/scratch/server.c
 * @author Avinal Kumar
 * @since February 03, 2021
 *
 * LAB 2 - Computer networks
 * Server program to receive file
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
    int sock1, sock2, clength;
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv, cli;

    //struct sockaddr_in server,client;

    memset(&serv, 0, sizeof(serv));
    memset(&cli, 0, sizeof(cli));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sock1, (struct sockaddr *)&serv, sizeof(serv));
    listen(sock1, 5);
    printf("Server started\n");
    clength = sizeof(cli);
    int i = 0;

    char buf[50];
    sock2 = accept(sock1, (struct sockaddr *)&cli, &clength);
    printf("\nClient Connected\n");
    printf("Receiving Files from Client...\n");
    sleep(4);
    FILE *fp = fopen("server.txt", "w");
    while (1)
    {
        //bzero(buf,sizeof(buf));
        read(sock2, buf, 50);
        if (strcmp(buf, "complete") == 0)
        {
            break;
        }
        fprintf(fp, "%s", buf);
    }
    printf("File Successfully reveived from Client\n");
    fclose(fp);
    printf("Content of the file is \n\n");
    FILE *rf = fopen("server.txt", "r");
    char c = fgetc(rf);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(rf);
    }

    fclose(rf);
    return 0;
}