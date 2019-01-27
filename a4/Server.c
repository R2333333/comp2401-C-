#include "Server.h"


int server()
{
    int myListenSocket, clientSocket;
    struct sockaddr_in  myAddr, clientAddr;
    int i, addrSize, bytesRcv;

    char buffer[80];
    char inString[80];
    /* create socket */

    myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (myListenSocket < 0) {
        printf("eek! couldn't open socket\n");
        exit(-1);
    }


    /* setup my server address */
    memset(&myAddr, 0, sizeof(myAddr));
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myAddr.sin_port = htons((unsigned short) MY_PORT);

    /* bind my listen socket */

    i = bind(myListenSocket, 
            (struct sockaddr *) &myAddr,
            sizeof(myAddr));
    if (i < 0) {
        printf("eek! couldn't bind socket\n");
        exit(-1);
    }


    /* listen */
    i = listen(myListenSocket, 5);
    if (i < 0) {
        printf("eek! couldn't listen\n");
        exit(-1);
    }


    /* wait for connection request */
    printf("Waiting for connection request...\n");

    addrSize = sizeof(clientAddr);

    clientSocket = accept(myListenSocket,
            (struct sockaddr *) &clientAddr,
            &addrSize);
    if (clientSocket < 0) {
        printf("eek! couldn't accept the connection\n");
        exit(-1);
    } else printf("...connection accepted\n");

    /* read message from client and do something with it */
    while (1) {
        //recieve message and print it out
        printf("Waiting to revieve...\n");
        bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesRcv] = 0;
        printf("Received->  %s\n", buffer);
        if(strcmp(buffer,"quit") == 0)
            break;
        myEncrypt(&(buffer[0]));
        printf("Received->  %s\n", buffer);
        printf("Your msg->  ");

        /* get input from user and send back to client */ 
        fgets(inString, sizeof(inString), stdin);
        inString[strlen(inString)-1] = 0;
        strcpy(buffer, inString);

        //break when get "quit"
        if(strcmp(inString, "quit") == 0){                                                                 
            strcpy(buffer, inString);                                                                     
            send(clientSocket, buffer, sizeof(buffer), 0);                                                
            break;                                                                                      
        }

        //encrypt and send the message
        myEncrypt(&(buffer[0]));
        send(clientSocket, buffer, strlen(buffer), 0);

    } 

    /* close sockets */

    close(myListenSocket);
    close(clientSocket);

    return 0;
}
