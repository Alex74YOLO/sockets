#include <stdio.h> //perror
#include <stdlib.h> //atoi
#include <unistd.h> //read, write, close
#include <arpa/inet.h> //sockaddr_in, AF_INET, SOCK_STREAM, socket etc..
#include <string.h> //memset

void die(char error[])
{
	perror(error);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int serverFd, clientFd;
	struct sockaddr_in server, client;
	int len;
	int port = 9002;
	char buffer[1024];

	if(argc == 2)
		port = atoi(argv[1]);

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverFd < 0)
		die("socket error");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	len = sizeof(server);

	if((bind(serverFd, (struct sockaddr *) &server, len)) < 0)
		die("bind error");
	
	if((listen(serverFd, 10)) < 0)
		die("listen error");

	while(1)
	{
		len = sizeof(client);
		printf("waiting...\n");
		
		if((clientFd = accept(serverFd, (struct sockaddr *) &client, &len)) < 0)
			die("accept error");

		char *client_ip = inet_ntoa(client.sin_addr);
		printf("Accepted new connection: %s : %d\n", client_ip, ntohs(client.sin_port));
		memset(buffer, 0, sizeof(buffer));
		
		int size = read(clientFd, buffer, sizeof(buffer));
		if(size < 0)
			die("read error");

		printf("received: '%s'\n", buffer);
		if(write(clientFd, buffer, size) < 0)
			die("write error");

		close(clientFd);
	}

	close(serverFd);

	return 0;
}
