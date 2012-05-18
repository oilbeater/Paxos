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

	fd = socket(AF_INET, SOCK_STREAM ,0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7777);
	address_len = sizeof(address);
	bind(fd, (struct sockaddr *)&address, address_len);

	listen(fd,100);

	while(1)
	{
		struct sockaddr_in client_address;
		int len;
		int client_sockfd;
		char *data = "Server to Client String!\n";
		char data2[100];

		printf("waiting...");
		fflush(stdout);

		len = sizeof(client_address);
		client_sockfd = accept(fd,(struct sockaddr *)&client_address, &len);

		read(client_sockfd, (void *)data2, 100);
		printf("Server read line:%s",data2);

		write(client_sockfd, (void *)data, strlen(data));
		printf("Server send lin:%s",data);
	}
	return 0;
}

