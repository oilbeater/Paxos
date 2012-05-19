prog: accepter1.c proposer.c learner1.c learner2.c
		gcc proposer.c -o proposer
		gcc learner1.c -o learner1
		gcc learner2.c -o learner2
		gcc -lpthread -o accepter1 accepter1.c
server: server.c
		gcc -lpthread -o server server.c
client: client.c
		gcc client.c -o client
clean: 
		rm server client learner
