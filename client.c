#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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
	int fd1;
	struct sockaddr_in address1;
	int address_len1;
	int rtval1;
	int len1;

	fd1 = socket(AF_INET, SOCK_STREAM, 0);

	address1.sin_family = AF_INET;
	address1.sin_addr.s_addr = inet_addr("127.0.0.1");
	address1.sin_port = htons(8888);
	address_len1 = sizeof(address1);
	rtval1 = connect(fd1, (struct sockaddr *)&address1, address_len1);
	if(rtval1 == -1) 
	{
		printf("connection failed\n");
		exit(1);
	}
	else
	{
		printf("connected\n");
	}

	char message[100];
	while(1)
	{
		memset((void*)message,0,100);
		printf("Please type promise id\n");
		scanf("%s",message);
		write(fd, (void *)message, strlen(message));
		printf("sent line:%s\n",message);
		memset((void *)data2,0,100);
		len = read(fd,(void *)data2,100);
		printf("readline:%s\n",data2);
		if(data2[0]=='1')
		{
			printf("Please type the id and message\n");
			memset((void*)message,0,100);
			scanf("%s",message);
			write(fd, (void *)message, strlen(message));
			printf("sent line:%s\n",message);
			memset((void *)data2,0,100);
			len = read(fd,(void *)data2,100);
			printf("readline:%s\n",data2);
			if(data2[0]=='1')
			{
				write(fd1,(void*)message, strlen(message));
			}
		}
		else
			continue;
	}
	printf("client exit.\n");

	close(fd);
	return 0;
}

