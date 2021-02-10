/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab3/client.c
 * @file client.c
 * @author Avinal Kumar
 * @since February 10, 2021
 *
 * Client implementation
 */

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

int main()
{
    char buf[100];
    int k;
    int sock_desc;
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_desc == -1)
    {
        printf("Error in socket creation");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    //client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port = 3002;

    k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));
    if (k == -1)
    {
        printf("Error in connecting to server");
        exit(1);
    }

    // image file size
    printf("Getting image size ...\n");
    FILE *data;
    data = fopen("SocialMedia.jpg", "r");
    int data_size = 0;
    fseek(data, 0, SEEK_END);
    data_size = ftell(data);
    fseek(data, 0, SEEK_SET);
    sleep(1);
    printf("Sending image size ...\n");
    write(sock_desc, &data_size, sizeof(data_size));
    sleep(1);

    // sending
    printf("Sending image, please wait ...\n");
    char send_buffer[data_size];
    sleep(2);
    int nb = fread(send_buffer, 1, sizeof(send_buffer), data);
    while (!feof(data))
    {
        write(sock_desc, send_buffer, nb);
        nb = fread(send_buffer, 1, sizeof(send_buffer), data);
    }

    sleep(2);
    printf("Image sent successfully !!");

    close(sock_desc);
    exit(0);
    return 0;
}