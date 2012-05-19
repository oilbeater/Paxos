#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <setjmp.h>

jmp_buf Jump_Buffer;

#define try if(!setjmp(Jump_Buffer))
#define catch else
#define throw longjmp(Jump_Buffer,1)

char *confirm_promise = "1 Promise Confirmed!";
char *confirm_send = "1 Send Confirm!";
char *reject_promise = "0 Promise Rejected!";
char *reject_send = "0 Send Reject";
char *reject_format = "0 Format Wrong";
char *data = "Server to Client String!\n";
int sn=0;

int check_promise(char data , int* sn)
{
	printf("now sn is %d",*sn);
	int rev=data-'0';
	if(0<=rev&&rev<=9&&rev>*sn)
		{
			*sn=rev;
			printf("promise request is %d now sn is %d\n",rev,*sn);
			return 1;
		}
	printf("promise request is %d now sn is %d\n",rev,*sn);
	return 0;
}

void* do_loop(void *clientdata)
{
	printf("create thread successful\n");
	int client_sockfd=*((int *)clientdata);
	try{
	while(1)
	{
		char data2[100];
		memset((void*)data2,0,100);
		read(client_sockfd, (void *)data2, 99);
		if(strlen(data2)==0)
			pthread_exit(NULL);
		printf("Server read line:%s\n",data2);
		if(data2[0]=='0')
		{
			if(check_promise(data2[2],&sn))
			{
				write(client_sockfd, (void *)confirm_promise, strlen(confirm_promise));
				printf("Server send line:%s\n",confirm_promise);
			}
			else
			{
				write(client_sockfd, (void *)reject_promise, strlen(reject_promise));
				printf("Server send line:%s\n",reject_promise);
			}
		}
		else
			if(data2[0]=='1')
			{
				printf("the id now is %d\n",data2[2]-'0');
				if(data2[2]-'0'==sn)
				{
					printf("Server confirm send\n");
					write(client_sockfd, (void *)confirm_send, strlen(data));
				}
				else
				{
					printf("server reject send\n");
					write(client_sockfd, (void *)reject_send, strlen(reject_promise));
				}
			}
			else
			{
				write(client_sockfd, (void *)reject_format, strlen(reject_promise));
			}
	}
	}
	catch{
	pthread_exit(NULL);}
}
int main()
{
	int fd;
	int address_len;
	struct sockaddr_in address;
	int listenfd;
	fd = socket(AF_INET, SOCK_STREAM ,0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7777);
	address_len = sizeof(address);
	bind(fd, (struct sockaddr *)&address, address_len);

	listenfd = listen(fd,100);

	while(1)
	{
		struct sockaddr_in client_address;
		int len;
		int client_sockfd;

		printf("waiting...\n");
		fflush(stdout);

		len = sizeof(client_address);
		client_sockfd = accept(fd,(struct sockaddr *)&client_address, &len);
		int ret;
		pthread_t p_thread;
		ret=pthread_create(&p_thread,NULL,do_loop,(void *) &client_sockfd);
		/*int pid;
		if(pid = fork() == 0)
		{
			close(listenfd);
			while(1)
			{
			char data2[100];
			memset((void*)data2,0,100);
			read(client_sockfd, (void *)data2, 100);
			printf("Server read line:%s\n",data2);
			if(data2[0]=='0')
			{
				if(check_promise(data2[2],&sn))
				{
					write(client_sockfd, (void *)confirm_promise, strlen(confirm_promise));
					printf("Server send line:%s\n",confirm_promise);
				}
				else
				{
					write(client_sockfd, (void *)reject_promise, strlen(reject_promise));
					printf("Server send line:%s\n",reject_promise);
				}
			}
			else
				if(data2[0]=='1')
				{
					if(data[2]-'0'==sn)
					{
						write(client_sockfd, (void *)data, strlen(data));
					}
					else
					{
						write(client_sockfd, (void *)reject_promise, strlen(reject_promise));
					}
				}
				else
				{
					write(client_sockfd, (void *)reject_promise, strlen(reject_promise));
				}

			}
			close(client_sockfd);
			exit(0);
		}*/
	}
	return 0;
}

