#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
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
		char *data = "Server to Client String!\n";

		printf("waiting...\n");
		fflush(stdout);

		len = sizeof(client_address);
		client_sockfd = accept(fd,(struct sockaddr *)&client_address, &len);

		while(1)
		{
		char data2[100];
		memset((void*)data2,0,100);
		read(client_sockfd, (void *)data2, 100);
		printf("Server read line:%s\n",data2);

		write(client_sockfd, (void *)data, strlen(data));
		printf("Server send line:%s\n",data);
		}
	}
	return 0;
}

