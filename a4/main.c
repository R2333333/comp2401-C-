#include "Server.h"

int main(int argc, char* args[]){
    key = *("101");
    counter = *("87");
    if (argc == 1)
        server();
    else
    {
        client(args[1]);
    }
    return 0;
}

void myEncrypt(char* inStr){
    for (int i = 0; i < strlen(inStr); ++i){
        char c = encrypt(counter, key);
        inStr[i] = c ^ inStr[i];
        counter++;
    }
}
