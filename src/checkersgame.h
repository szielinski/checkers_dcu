#ifndef CHECKERSGAME_H
#define CHECKERSGAME_H

#include "game.h"

class CheckersGame : public Game
{
	public:		
		CheckersGame();
		~CheckersGame();
		int checkWin();
		bool doMove(std::string move, int player);
	private:
		bool isValid(int owner, int originX, int originY, int destX, int destY);
		int	noP1pieces;
		int	noP2pieces;
		int player1;
		int player2;
};

#endif
