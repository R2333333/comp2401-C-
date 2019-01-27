#ifndef SERVER_H
#define SERVER_H
#define MY_PORT 60002
#define SERVER_PORT 60002                                                                                                                                               

#include <stdio.h>                                                                                  
#include <stdlib.h>                                                                                 
#include <string.h>                                                                                 
#include <unistd.h>                                                                                 
#include <sys/types.h>                                                                              
#include <sys/socket.h>                                                                             
#include <netinet/in.h>                                                                             
#include <arpa/inet.h>

//        int Server();
//        int Server(char*[]);

int server();
/*int myListenSocket, clientSocket;
struct sockaddr_in  myAddr, clientAddr;
int i, addrSize, bytesRcv;

char buffer[80];
char inString[80];
*/
char encrypt(char, char);                                                                           
unsigned char key, counter;
int client(char*); 
void myEncrypt(char*);

#endif
