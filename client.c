#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd;
	struct sockaddr_in address;
	int address_len;
	int rtval;
	char *data = "Client to Server string!\n";
	char data2[100];
	char *data1 = "I receive your reply!\n";
	int len;

	while(1)
	{
	fd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7777);
	address_len = sizeof(address);
	rtval = connect(fd, (struct sockaddr *)&address, address_len);
	if(rtval == -1) 
	{
		printf("connection failed\n");
		exit(1);
	}
	else
	{
		printf("connected\n");
	}

	write(fd, (void *)data1, strlen(data1));
	printf("sent line:%s",data);
	len = read(fd,(void *)data2,100);
	printf("readline:%s",data2);
	printf("client exit.\n");
	close(fd);
	}
	return 0;
}

