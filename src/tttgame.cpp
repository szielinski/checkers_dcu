#include <iostream>
#include <stdlib.h>

#include "tttgame.h"
#include "board.h"
#include "piece.h"

TTTGame::TTTGame()
{
	board = new Board(3);
}

TTTGame::~TTTGame()
{
	delete board;
}

/*
	Check for a winner, 
	returns -1 if there is no winner, 
	1 if player1 won,
	2 if player2 won.
*/
int TTTGame::checkWin()
{	
	// at least 5 moves need to be made before there can be a winner
	if((*board).getNoPieces() < 5)
		return -1;
	
	
	for(int i=0; i < (*board).getSize(); i++)
	{	
		// check for winner accross columns
		if(	(*board).getOwnerAt(0, i) != 0 
			&& (*board).getOwnerAt(0, i) == (*board).getOwnerAt(1, i) 
			&& (*board).getOwnerAt(1, i) == (*board).getOwnerAt(2, i) )
			return (*board).getOwnerAt(0, i);
			
		// check for winner accross rows
		if(	(*board).getOwnerAt(i, 0) != 0 
			&& (*board).getOwnerAt(i, 0) == (*board).getOwnerAt(i, 1) 
			&& (*board).getOwnerAt(i, 1) == (*board).getOwnerAt(i, 2) )
			return (*board).getOwnerAt(i, 0);
	}	
	
	// check diagonally 
	if(	(*board).getOwnerAt(0, 0) != 0 
		&& (*board).getOwnerAt(0, 0) == (*board).getOwnerAt(1, 1) 
		&& (*board).getOwnerAt(1, 1) == (*board).getOwnerAt(2, 2) )
		return (*board).getOwnerAt(0, 0);
	if(	(*board).getOwnerAt(0, 2) != 0 
		&& (*board).getOwnerAt(0, 2) == (*board).getOwnerAt(1, 1) 
		&& (*board).getOwnerAt(1, 1) == (*board).getOwnerAt(2, 0) )
		return (*board).getOwnerAt(0, 2);	
	//winner hasn't been found	
	return -1;
}

/* 
	move based on a string of the form "a1", where 
	a is a char, range: 'a..c'
	1 is an int, range: '1..3'
	a1 is the cell that the player wants to mark
	"player" is the player who is trying to make a move 
*/
bool TTTGame::doMove(std::string move, int player)
{
	char type = ' ';
	if(player == 1) 
		type = 'O';
	else
		type = 'X'; 
	int y = (int) move[0];
	y -= 97;
	int x = (int) move[1];
	x -= 49;	
	if(!isValid(x, y))
		return false;
	Piece * s = new Piece(player, type);
	(*board).addPiece(s, x, y);
	return true;
}

bool TTTGame::isValid(int x, int y)
{
	if(x > (*board).getSize())
		return false;
	if(y > (*board).getSize())
		return false;
	if((*board).getOwnerAt(x, y) != 0)
		return false;
	return true;
}
