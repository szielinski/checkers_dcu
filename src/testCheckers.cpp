#include <iostream>

#include "checkersgame.h"
#include "piece.h"
#include "board.h"

int main()
{
	CheckersGame s;
	(*s.getBoard()).display();
	std::string move = "b3 a4";
	std::string move1 = "c6 b5";
	std::string move2 = "a4 c6";
	std::string move3 = "d7 b5";
	s.doMove(move, 2);
	(*s.getBoard()).display();
	s.doMove(move1, 1);
	(*s.getBoard()).display();
	s.doMove(move2, 2);
	(*s.getBoard()).display();
	s.doMove(move3, 1);
	(*s.getBoard()).display();
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	return 0;
}
