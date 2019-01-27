DEBUG= 

a4: main.o Server.o Client.o a4-util.o
	gcc $(DEBUG) -o a4 main.o Server.o Client.o a4-util.o

main.o: main.c
	gcc $(DEBUG) -c main.c

Server.o:	Server.c
	gcc $(DEBUG) -c Server.c

Client.o:	Client.c 
	gcc $(DEBUG) -c Client.c 

clean:
	rm -f Client.o Server.o main.o a4
