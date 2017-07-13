all: client server

clean:
	rm client server

program1: client.c
	gcc -o client client.c

program2: server.c
	gcc -o server server.c
