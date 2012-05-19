prog: server.c client.c learner.c
		gcc client.c -o client
		gcc learner.c -o learner
		gcc -lpthread -o server server.c
server: server.c
		gcc -lpthread -o server server.c
client: client.c
		gcc client.c -o client
clean: 
		rm server client learner
