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
	char data3[100];
	char data4[100];
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
	}
	else
	{
		printf("connected\n");
	}
	int fd3;
	struct sockaddr_in address3;
	int address_len3;
	int rtval3;
	int len3;

	fd3 = socket(AF_INET, SOCK_STREAM, 0);

	address3.sin_family = AF_INET;
	address3.sin_addr.s_addr = inet_addr("127.0.0.1");
	address3.sin_port = htons(7778);
	address_len3 = sizeof(address3);
	rtval3 = connect(fd3, (struct sockaddr *)&address3, address_len3);
	if(rtval3 == -1) 
	{
		printf("connection failed\n");
	}
	else
	{
		printf("connected\n");
	}

	int fd4;
	struct sockaddr_in address4;
	int address_len4;
	int rtval4;
	int len4;

	fd4 = socket(AF_INET, SOCK_STREAM, 0);

	address4.sin_family = AF_INET;
	address4.sin_addr.s_addr = inet_addr("127.0.0.1");
	address4.sin_port = htons(7779);
	address_len4 = sizeof(address4);
	rtval4 = connect(fd4, (struct sockaddr *)&address4, address_len4);
	if(rtval4 == -1) 
	{
		printf("connection failed\n");
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
	}
	else
	{
		printf("connected\n");
	}
	int fd2;
	struct sockaddr_in address2;
	int address_len2;
	int rtval2;
	int len2;

	fd2 = socket(AF_INET, SOCK_STREAM, 0);

	address2.sin_family = AF_INET;
	address2.sin_addr.s_addr = inet_addr("127.0.0.1");
	address2.sin_port = htons(8889);
	address_len2 = sizeof(address2);
	rtval2 = connect(fd2, (struct sockaddr *)&address2, address_len2);
	if(rtval2 == -1) 
	{
		printf("connection failed\n");
	}
	else
	{
		printf("connected\n");
	}
	char message[100];
	while(1)
	{
		int promise_num=0;
		int send_num=0;
		memset((void*)message,0,100);
		printf("Please type promise id\n");
		scanf("%s",message);
		if(fork()==0)
		{
			write(fd3, (void *)message, strlen(message));
			exit(0);
		}
		if(fork()==0)
		{
			write(fd4, (void *)message, strlen(message));
			exit(0);
		}
		if(fork()==0)
		{
			write(fd, (void *)message, strlen(message));
			exit(0);
		}
		printf("sent line:%s\n",message);
		memset((void *)data2,0,100);
		read(fd,(void *)data2,100);
		read(fd3,(void *)data3,100);
		read(fd4,(void *)data4,100);
		if(strlen(data2)!=0&&data2[0]=='1')
			promise_num++;
		if(strlen(data3)!=0&&data3[0]=='1')
			promise_num++;
		if(strlen(data4)!=0&&data4[0]=='1')
			promise_num++;
		if(promise_num>=2)
		{
			printf("Please type the id and message\n");
			memset((void*)message,0,100);
			scanf("%s",message);
			if(fork()==0)
			{
				write(fd, (void *)message, strlen(message));
				exit(0);
			}
			if(fork()==0)
			{
				write(fd3, (void *)message, strlen(message));
				exit(0);
			}
			if(fork()==0)
			{
				write(fd4, (void *)message, strlen(message));
				exit(0);
			}
			printf("sent line:%s\n",message);
			memset((void *)data2,0,100);
			memset((void *)data3,0,100);
			memset((void *)data4,0,100);
			read(fd,(void *)data2,100);
			read(fd3,(void *)data3,100);
			read(fd4,(void *)data4,100);
			if(strlen(data2)!=0&&data2[0]=='1')
				send_num++;
			if(strlen(data3)!=0&&data3[0]=='1')
				send_num++;
			if(strlen(data4)!=0&&data4[0]=='1')
				send_num++;

			printf("the send num is %d\n",send_num);
			if(send_num>=2)
			{
				if(fork()==0)
				{
					write(fd1,(void*)message, strlen(message));
					exit(0);
				}
				if(fork()==0)
				{
					write(fd2,(void*)message, strlen(message));
					exit(0);
				}
			}
		}
		else
			continue;
	}
	printf("client exit.\n");

	close(fd);
	return 0;
}

