#include <iostream>
#include <stdlib.h>

#include "checkersgame.h"
#include "board.h"
#include "piece.h"

// set up the game, with player 1 starting at the bottom and player 2 starting at the top of the board
CheckersGame::CheckersGame()
{	
	const char type1 = 'O';
	const char type2 = 'X'; 
	const int noPieces = 12;
	noP1pieces = 12;
	noP2pieces = 12;
	player1 = 1;
	player2 = 2;
	board = new Board(8);	
	
	// initialise the starting positions
	// row 7
	for(int i=0; i<(*board).getSize(); i+=2)
	{
		Piece * s = new Piece(player1, type1);
		(*board).addPiece(s, 7, i);
	}
	// row 6
	for(int i=1; i<(*board).getSize(); i+=2)	
	{
		Piece * s = new Piece(player1, type1);
		(*board).addPiece(s, 6, i);
	}
	// row 5
	for(int i=0; i<(*board).getSize(); i+=2)	
	{
		Piece * s = new Piece(player1, type1);
		(*board).addPiece(s, 5, i);
	}
	
	// row 0
	for(int i=1; i<(*board).getSize(); i+=2)
	{
		Piece * s = new Piece(player2, type2);
		(*board).addPiece(s, 0, i);
	}
	// row 1
	for(int i=0; i<(*board).getSize(); i+=2)
	{
		Piece * s = new Piece(player2, type2);
		(*board).addPiece(s, 1, i);
	}
	// row 2
	for(int i=1; i<(*board).getSize(); i+=2)
	{
		Piece * s = new Piece(player2, type2);
		(*board).addPiece(s, 2, i);
	}
}

CheckersGame::~CheckersGame()
{
	delete board;
}

// check if a player has won
int CheckersGame::checkWin()
{		
	if(noP1pieces == 0)
		return player1;
	if(noP2pieces == 0)
		return player2;
	return -1;
}

/* 
	move based on a string of the form "a1 b2", where 
	a and b are chars range: 'a..h'
	1 and 2 are ints range: '1..8'
	a1 is the location of the piece to be moved
	b2 is the destination - where to move the piece 
	"player" is the player who is trying to make a move 
*/
bool CheckersGame::doMove(std::string move, int player)
{
	// convert ascii characters to integers
	int originY = (int) move[0];
	originY -= 97;
	int originX = (int) move[1];
	originX -= 49;	
	int destY = (int) move[3];
	destY -= 97;
	int destX = (int) move[4];
	destX -= 49;	
	
	// check if the move is valid
	if(!isValid(player, originX, originY, destX, destY))
		return false;
	
	int tempOwner;
	// remove the opponent's piece that is beaten by the move
	// for any player that is moving down the board
	if(destX - originX == 2)
	{
		if(destY-originY > 0)
		{
			tempOwner = (*board).getOwnerAt((originX + 1), (originY + 1));
			(*board).removePieceAt((originX + 1), (originY + 1));
		}
		else
		{
			tempOwner = (*board).getOwnerAt((originX + 1), (originY - 1));
			(*board).removePieceAt((originX + 1), (originY - 1));			
		}
		if(tempOwner == 1)
			noP1pieces--;
		else if(tempOwner == 2)
			noP2pieces--;			
	}
	//for any player that is moving up the board
	else if(destX - originX == -2)
	{
		if(destY-originY > 0)
		{
			tempOwner = (*board).getOwnerAt((originX - 1), (originY + 1));
			(*board).removePieceAt((originX - 1), (originY + 1));
		}
		else
		{
			tempOwner = (*board).getOwnerAt((originX - 1), (originY - 1));
			(*board).removePieceAt((originX - 1), (originY - 1));			
		}
		if(tempOwner == 1)
			noP1pieces--;
		else if(tempOwner == 2)
			noP2pieces--;	
	}
	
	// move the player's piece
	Piece temp = (*(*board).getPieceAt(originX, originY));
	(*board).removePieceAt(originX, originY);
	(*board).addPiece(&temp, destX, destY);	
	
	return true;
}

// check if a move is valid
bool CheckersGame::isValid(int player, int originX, int originY, int destX, int destY)
{
	// check if the move is within the limits of the board
	if(originX > (*board).getSize())
		return false;
	if(originY > (*board).getSize())
		return false;
	if(destX > (*board).getSize())
		return false;
	if(destY > (*board).getSize())
		return false;
		
	// check if the player is trying to move other player's piece
	if((*board).getOwnerAt(originX, originY) != player)
		return false;
		
	// check if the player is not trying to move into an occupied space
	if((*board).getOwnerAt(destX, destY) != 0)
		return false;
	
	// if player 2
	if(player == player2)
	{
		// if moving by 1 space
		if((originX +1) == destX)
		{			
			if(!((originY+1 == destY) || (originY-1 == destY)))
				return false;
		}
		
		// if moving by 2 spaces
		else if((originX +2) == destX)
		{			
			// if moving to the right of the board
			if(destY-originY > 0)
			{
				// the middle space (between origin and destination) has to have a piece belonging to the other player
				if((*board).getOwnerAt((1 + originX), (originY + 1)) != player1)
					return false;
			}
			// if moving to the left
			else		
			{
				// the middle space (between origin and destination) has to have a piece belonging to the other player
				if((*board).getOwnerAt((originX + 1), (originY - 1)) != player1)
					return false;
			}
			// check if the piece moves by 2 spaces and 2 spaces only
			if(!((originY+2 == destY) || (originY-2 == destY)))
				return false;
		}
		else return false;
		
		return true;
	}
	// if player 1 
	else if(player == player1)
	{
		// if moving by 1 space
		if((originX -1) == destX)
		{
			if(!((originY+1 == destY) || (originY-1 == destY)))
				return false;
		}
		//if moving by 2 spaces
		else if((originX -2) == destX)
		{					
			// if moving to the right of the board
			if(destY-originY > 0)
			{
				// the middle space (between origin and destination) has to have a piece belonging to the other player
				if((*board).getOwnerAt((originX - 1), (originY + 1)) != player2)
				{
					return false;
				}
			}
			// if moving to the left
			else		
			{
				// the middle space (between origin and destination) has to have a piece belonging to the other player
				if((*board).getOwnerAt((originX - 1), (originY - 1)) != player2)
				{
					return false;
				}
			}
			// check if the piece moves by 2 spaces and 2 spaces only
			if(!((originY+2 == destY) || (originY-2 == destY)))
			{
				return false;
			}
		}
		else return false;
		
		return true;
	}
	return true;
	// A PLAYER CANNOT MOVE BACKWARDS!!! ALSO, ANOTHER TYPE FOR A PIECE THAT CAN MOVE BACKWARDS SHOULD BE ADDED
}

