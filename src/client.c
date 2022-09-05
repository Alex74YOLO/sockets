#include <stdio.h> //perror
#include <stdlib.h> //atoi
#include <unistd.h> //write, read, close
#include <arpa/inet.h> //sockaddr_in...
#include <string.h> //memset

void die(char *error)
{
	perror(error);
	exit(1);
}

const char message[] = "Hello\n";

int main(int argc, char const *argv[])
{
	int serverFd;
	struct sockaddr_in server;
	int len;
	int port = 9002;
	char *server_ip = "127.0.0.1";
	char *buffer = "hello server";
	
	if(argc == 3)
	{
		server_ip = argv[1];
		port = atoi(argv[2]);
	}
	
	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverFd < 0)
		die("socket error");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_port = htons(port);

	len = sizeof(server);

	if(connect(serverFd, (struct sockaddr *) &server, len) < 0)
		die("connect error");

	if(write(serverFd, buffer, strlen(buffer)) < 0)
		die("write error");

	char recv[1024];
	memset(recv, 0, sizeof(recv));
	
	if(read(serverFd, recv, sizeof(recv)) < 0)
		die("read error");

	printf("%s from server\n", recv);

	close(serverFd);

	return 0;
}
