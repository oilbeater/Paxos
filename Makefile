prog: accepter1.c accepter2.c accepter3.c proposer.c learner1.c learner2.c
		gcc proposer.c -o proposer
		gcc learner1.c -o learner1
		gcc learner2.c -o learner2
		gcc -lpthread -o accepter1 accepter1.c
		gcc -lpthread -o accepter2 accepter2.c
		gcc -lpthread -o accepter3 accepter3.c
clean: 
		rm accepter1 accepter2 accepter3 proposer learner1 learner2
