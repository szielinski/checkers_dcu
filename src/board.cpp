#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "board.h"
#include "piece.h"

Board::Board(int arg_size)
{
	noPieces = 0;
	size = arg_size;
	
	pieceArray = new Piece *[size];
	
	for(int i=0; i<size; i++)
		pieceArray[i] = new Piece[size];
}

Board::~Board()
{
	for(int i=0; i<size; i++)
		delete [] pieceArray[i];
	delete [] pieceArray;
}

void Board::addPiece(Piece *piece, int x, int y)
{	
	if( (x >= size || x < 0) || (y >= size || y < 0) )
	{ 	
		std::cout << "\naddPiece ArrayOutOfBoundsError\n" << x << y;
		exit (1);
	}
	
	pieceArray[size-1-x][y] = *piece;	
	noPieces++;
}

void Board::removePieceAt(int x, int y)
{
	if( (x >= size || x < 0) || (y >= size || y < 0) )
	{ 	
		std::cout << "\nremovePieceAt ArrayOutOfBoundsError\n";
		exit (1);
	}
	
	Piece s;
	pieceArray[size-1-x][y] = s;
	noPieces--;	
}

std::string Board::display()
{
	std::stringstream output;
	
	output << std::endl;
	char temp = 'a';	
	for(int i=0; i<size; i++)
	{
		output << "   " << temp++;
	}
	output << std::endl;
	for(int i=0; i<size; i++)
	{
		output << size-i << " ";;
		for(int j=0; j<size; j++)
		{
			output << "[";
			output << pieceArray[i][j].display();
			output << "] ";
		}
		output << std::endl;
	}			
	
	return output.str();
}

Piece * Board::getPieceAt(int x, int y)
{
	if( (x >= size || x < 0) || (y >= size || y < 0) )
	{ 	
		std::cout << "\ngetPieceAt ArrayOutOfBoundsError\n";
		exit (1);
	}
	return &pieceArray[size-1-x][y];
}

int Board::getOwnerAt(int x, int y)
{	
	if( (x >= size || x < 0) || (y >= size || y < 0) )
	{ 	
		std::cout << "\ngetOwnerAt ArrayOutOfBoundsError\n" << x << y;
		exit (1);
	}
	return pieceArray[size-1-x][y].getOwner();
}
int Board::getNoPieces() const
{	
	return noPieces;
}

int Board::getSize() const
{
	return size;
}
