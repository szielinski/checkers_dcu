#ifndef BOARD_H
#define BOARD_H

#include <string>

class Piece;

class Board
{
	public:
		//Creates and initialises a size*size board
		Board(int arg_size);
		~Board();
		
		//Adds given piece to board at (x,y)
		void addPiece(Piece *piece, int x, int y);
		//Displays the boards current position
		std::string display();
		//Remove the piece at given location
		void removePieceAt(int x, int y);
		//Returns the piece at given location
		Piece * getPieceAt(int x, int y);
		//Returns the owner of the piece at given location
		int getOwnerAt(int x, int y);
		//Returns size of board.
		int getSize() const;
		//Returns number of pieces on the board
		int getNoPieces() const;
			
	private:
		int noPieces;
		int size;
		
		Piece **pieceArray;
};

#endif
