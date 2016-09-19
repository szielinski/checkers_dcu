#ifndef GAME_H
#define GAME_H

class Board;

class Game
{
	public:
		//Checks for a winner
		virtual int checkWin() = 0;
		//Does a move specified by the string given, returns true if successful, false if move is invalid for some reason.
		virtual bool doMove(std::string move, int player) = 0;		
		//Returns the board associated with the game.
		Board *getBoard() { return board; };
	
	protected:
		Board *board;
};

#endif
