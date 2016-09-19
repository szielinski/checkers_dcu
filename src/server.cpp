/*
** Networking code based on "Simple Stream Server" example.
** Found at http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
*/

#include "server.h"

#include "board.h"
#include "checkersgame.h"
#include "tttgame.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include <iostream>

#define LINELEN 50	//How long a line can be, at maximum.
#define BACKLOG 2	// how many pending connections queue will hold


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Server::Server(char *port)
{
	this->port = port;
	//Initialise sockets to -1
	playfd[0] = playfd[1] = -1;
}

Server::~Server()
{
}

void Server::start()
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		return;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server: waiting for connections...\n");
	
	sin_size = sizeof their_addr;
	
	//Accept the first player.
	do {
		playfd[0] = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	} while (playfd[0] == -1);

	inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *)&their_addr),
		s, sizeof s);
	printf("Player one connected from %s\n", s);
	
	getGameType();
	getPlayerName(0);
	
	//Accept the second player.
	do {
		playfd[1] = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	} while (playfd[1] == -1);
	
	inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *)&their_addr),
		s, sizeof s);
	printf("Player two connected from %s\n", s);

	getPlayerName(1);

	return;
}

void Server::sendMessage(std::string message, int player)
{
	if (send(playfd[player], message.c_str(), message.size(), 0) == -1) {
		std::cout << "Error sending message to player " << (player + 1) << "Exiting.\n";
		exit(1);
	}
}

void Server::gameLoop()
{
	char move[LINELEN];
	int moveNum = 0;
	
	if (gametype == 1) {
		gameSession = new CheckersGame();
	} else {
		gameSession = new TTTGame();
	}
	
	while (true) {
		if (gameSession->checkWin() != -1) {
			int winner = gameSession->checkWin() - 1;
			char winMsg[60];
			sprintf(winMsg, "Winner: <%s>", playnames[winner]);
			sendMessage(winMsg, 0);
			sendMessage(winMsg, 1);
			
			return;
		}
		
		sendMessage(gameSession->getBoard()->display(), moveNum % 2);
		
		sendMessage("Please enter your move >", moveNum % 2);
		getLine(moveNum % 2, move, LINELEN);
		
		std::cout << move;
		
		if (gameSession->doMove(move, (moveNum % 2) + 1)) {
			moveNum++;
		} else {
			sendMessage("Invalid move!\n", moveNum % 2);
		}
	}
}

void Server::closeConnection()
{
	std::cout << "Game over. Winner was player " << gameSession->checkWin() << std::endl;
	close(playfd[0]);
	close(playfd[1]);
}

void Server::getGameType()
{
	char buf[LINELEN];
	int type;
	
	do {
		sendMessage("Please enter gametype (1 for Checkers, 2 for Tic-Tac-Toe) >", 0);
	
		if (getLine(0, buf, LINELEN)) {
			std::cerr << "Error reading gametype.\n";
			exit(1);
		}
		type = atoi(buf);
		
		if (type == 1) {
			std::cout << "Checkers.\n";
		} else if (type == 2) {
			std::cout << "TTT.\n";
		}
	} while (type < 1 || type > 2);
	
	gametype = type;
}

void Server::getPlayerName(int player)
{
	sendMessage("Please enter your name >", player);
	
	if (!(playnames[player] = (char*)calloc(50, sizeof(char)))) {
		std::cerr << "Error allocating memory for player name.\n";
		exit(1);
	}
	if (getLine(player, playnames[player], LINELEN)) {
		std::cerr << "Error reading player name.\n";
		exit(1);
	}
}

bool Server::getLine(int player, char *line, int maxLen)
{
	do {
		recv(playfd[player], line, 1, 0);
		if (line[0] == '\n') {
			//We've reached the end of the line, success!
			line[0] = '\0';
			return false;
		}
		
		line++;
	} while(line < line+50);
	
	//Line was too long, error.
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <portnum>." << std::endl;
		return 1;
	}
	Server *s = new Server(argv[1]);
	s->start();
	s->gameLoop();
	s->closeConnection();
	return 0;
}

