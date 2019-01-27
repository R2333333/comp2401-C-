#include "Server.h"

int client(char* serverIP)
{
    int mySocket;
    struct sockaddr_in  addr;
    int i, bytesRevC;

    char inStr[80];
    char bufferC[80];

    mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mySocket < 0) {
        printf("eek! couldn't open socket\n");
        exit(-1);
    }


    /* setup address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(serverIP);
    addr.sin_port = htons((unsigned short) SERVER_PORT);

    /* connect to server */
    printf("Connecting to server ...\n");
    i = connect(mySocket, 
            (struct sockaddr *) &addr,
            sizeof(addr));
    if (i<0) {
        printf("client could not connect!\n");
        exit(-1);
    }else printf("...Connected\n");

    /* get input from user and send to server */
    while (1) {
        printf("Your msg->  ");
        //    scanf("%s", inStr);
        fgets(inStr, sizeof(inStr), stdin);
        inStr[strlen(inStr)-1] = 0;

        //break when quit was entered
        if(strcmp(inStr, "quit") == 0){
            strcpy(bufferC, inStr);
            send(mySocket, bufferC, sizeof(bufferC), 0);
            break;
        }
        //encrypt and send
        myEncrypt(&(inStr[0]));
        strcpy(bufferC, inStr);
        send(mySocket, bufferC, sizeof(bufferC), 0);

        //recieve mesage from the server
        printf("Waiting to revieve...\n");
        bytesRevC = recv(mySocket, bufferC, sizeof(bufferC), 0);
        bufferC[bytesRevC] = 0;
        printf("Received->  %s\n", bufferC); 
        if(strcmp(bufferC,"quit") == 0)                                                                  
            break;                                                                                        
        myEncrypt(&(bufferC[0]));
        printf("Received->  %s\n", bufferC);
    } 

    /* close the socket */

    close(mySocket);

    return 0;
}

