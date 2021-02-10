/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab3/server.c
 * @file server.c
 * @author Avinal Kumar
 * @since February 10, 2021
 *
 * Server Implementation
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
    socklen_t len;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
    {
        printf("Error in socket creation");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    //server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port = 3002;

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
    {
        printf("Error in binding");
        exit(1);
    }

    k = listen(sock_desc, 20);
    if (k == -1)
    {
        printf("Error in listening");
        exit(1);
    }

    len = sizeof(client); //VERY IMPORTANT
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc == -1)
    {
        printf("Error in temporary socket creation");
        exit(1);
    }

    printf("Getting image size ...\n");
    int data_size;
    read(temp_sock_desc, &data_size, sizeof(int));

    printf("Getting image, please wait ...\n");
    char receive_buf[data_size];
    FILE *image;
    image = fopen("received.jpg", "w");
    int nb = read(temp_sock_desc, receive_buf, data_size);
    while (nb > 0)
    {
        fwrite(receive_buf, 1, nb, image);
        nb = read(temp_sock_desc, receive_buf, data_size);
    }

    fclose(image);
    sleep(2);
    printf("Image received successfully !!");

    close(temp_sock_desc);

    exit(0);
    return 0;
}