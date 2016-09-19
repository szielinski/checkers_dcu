#ifndef TTTGAME_H
#define TTTGAME_H

#include "game.h"

class TTTGame : public Game
{
	public:		
		TTTGame();
		~TTTGame();
		// check for a winner, returins -1 if there is none
		int checkWin();
		//Does a move specified by the string given, returns true if successful, false if move is invalid for some reason.
		bool doMove(std::string move, int player);
	private:
		bool isValid(int x, int y);
};

#endif
