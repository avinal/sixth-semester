# LAB 1 - Computer Networks 

## Files

| File Name | Description |
| --- | --- |
| [TCP_client.c](TCP_client.c) | TCP client implementation |
| [TCP_server.c](TCP_server.c) | TCP server implementation |
| [UDPclient.c](UDPclient.c) | UDP client implementation |
| [UDPserver.c](UDPserver.c) | UDP server implementation |

## Questions

1. Change the binding socket port Number of the client and the server sockets (Note that port No. 0 to 1023 are reserved for common TCP/IP applications and cannot be used).

2. Change the number of outstanding incoming request for the listen() primitive to 10, so that it can keep 10 incoming requests in pipe at a time.

3. Change the binding address of both the client and the server sockets from "INADDR_ANY" to the IP address of the local host.

4. Change the input buffer size of the client and the server to 4096. Modify the texts exchanged between the client and the server so that texts of larger length are exchanged.

## Student Details

- Name: Avinal Kumar
- Roll: 185067
- Branch: CSE
- Date: 27 Jan 2021