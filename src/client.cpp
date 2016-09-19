/*
** Networking code based on "Simple Stream Client" example.
** Found at http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
*/

#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <iostream>

#define MAXDATASIZE 256 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Client::Client(char *host, char *port)
{
	this->host = host;
	this->port = port;
	
	sockfd = -1;
}

Client::~Client()
{
}

bool Client::join()
{
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return true;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure

	return false;
}

void Client::gameLoop()
{
	char input[500];

	while(true) {
		std::string line = getMessage();
		std::cout << line;
		
		if (line.find("Winner: <") != -1) {
			return;
		}
		
		if (line[line.size() - 1] != '>') {
			continue;
		}
		
		std::cin.getline(input, 500);
		input[strlen(input) + 1] = '\0';
		input[strlen(input)] = '\n';
		
		sendMessage(input);
	}

	close(sockfd);
}

void Client::disconnect()
{
	std::cout << "\nDisconnecting." << std::endl;
	close(sockfd);
}

void Client::sendMessage(std::string message)
{
	if (send(sockfd, message.c_str(), message.size(), 0) == -1) {
		std::cout << "Error sending message to server. Exiting.\n";
		exit(1);
	}
}

std::string Client::getMessage()
{
	char buf[MAXDATASIZE];
	int i=0;
	
	do {
		recv(sockfd, buf+i, 1, 0);
		if (buf[i] == '>' || buf[i] == '\n') {
			//We've reached the end of the line, success!
			buf[i+1] = '\0';
			return std::string(buf);
		}
		
		i++;
	} while(i < MAXDATASIZE - 1);
	
	std::cerr << "Receiving invalid messages from server. Exitting.\n" << std::endl;
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " hostname port\n";
		exit(1);
	}
	
	Client *c = new Client(argv[1], argv[2]);
	if (c->join()) {
		std::cerr << "Failed to connect to server." << std::endl;
		exit(1);
	}
	c->gameLoop();
	c->disconnect();
	return 0;
}

