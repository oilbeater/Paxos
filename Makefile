prog: server.c client.c
		gcc client.c -o client
		gcc server.c -o server
server: server.c
		gcc server.c -o server
client: client.c
		gcc client.c -o client
clean: 
		rm server client
