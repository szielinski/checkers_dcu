#ifndef SERVER_H
#define SERVER_H

#include <string>

class Client;
class Game;

class Server
{
	public:
		//Create a server to listen on a given port
		Server(char *port);
		~Server();
		
		//Starts the server after initialisation and waits for both players
		void start();
		//Closes connections.
		void closeConnection();
		//Sends data to client
		void sendMessage(std::string message, int player);
		//run the main game loop after starting (i.e. listen for message, act, repeat).
		void gameLoop();
	
	private:
		char *port;
		
		//Type of game, 1 for checkers, 2 for TTT.
		int gametype;
		
		//Socket to listen on.
		int sockfd;
		
		//Sockets and names for client 1 and 2.
		int playfd[2];
		char *playnames[2];
		
		Game *gameSession;
		
		//Gets game type from player 1
		void getGameType();
		//Gets the players name
		void getPlayerName(int player);
		
		//Gets a line of text from a player, returns true if fail.
		bool getLine(int player, char *line, int maxLen);
};

#endif
