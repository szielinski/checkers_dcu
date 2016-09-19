#include <iostream>

#include "piece.h"
#include "board.h"

int main()
{
	Board b1(3);
	
	Piece s (5, 'X');
	Piece s1 (4, 'O');
	Piece s2 (5, 'X');
	
	b1.display();
	b1.addPiece(&s, 0, 1);
	b1.display();
	b1.addPiece(&s1, 1, 1);
	b1.display();
	b1.addPiece(&s2, 2, 1);
	b1.display();
	b1.removePieceAt(2, 1);
	b1.display();
	std::cout << b1.getOwnerAt(1, 1);
	std::cout << b1.getOwnerAt(0, 0);
	return 0;
}
