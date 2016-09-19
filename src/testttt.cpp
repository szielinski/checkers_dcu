#include <iostream>

#include "tttgame.h"
#include "piece.h"
#include "board.h"

int main()
{
	TTTGame s;
	std::string move = "a1";
	std::string move1 = "a2";
	std::string move2 = "b1";
	std::string move3 = "c1";
	std::string move4 = "b2";
	
	s.doMove(move, 2);
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	s.doMove(move1, 1);
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	s.doMove(move2, 2);
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	s.doMove(move4, 1);	
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	s.doMove(move3, 2);	
	if(s.checkWin() != -1)
		return 0;
	(*s.getBoard()).display();
	
	return 0;
}
