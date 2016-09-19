#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
	public:
		//Creates a client with given name.
		Client(char *host, char *port);
		~Client();
		
		//Attempt to join the given server (IP or hostname) on given port.
		//Returns true if fail.
		bool join();
		//Sends message to server.
		void sendMessage(std::string message);
		//Receives message from server.
		std::string getMessage();
		//Starts game loop (get command from user, give to server, await response, repeat)
		void gameLoop();
		//Disconnects from server
		void disconnect();
	
	private:
		char *host, *port;
		
		int sockfd;
};

#endif
