#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

char *confirm_promise = "1 Promise Confirmed!";
char *reject_promise = "0 Promise Rejected!";

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
int main()
{
	int fd;
	int address_len;
	struct sockaddr_in address;
	int listenfd;
	int sn=0;
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
		char *data = "Server to Client String!\n";

		printf("waiting...\n");
		fflush(stdout);

		len = sizeof(client_address);
		client_sockfd = accept(fd,(struct sockaddr *)&client_address, &len);
		int pid;
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
		}
		close(client_sockfd);
	}
	return 0;
}

