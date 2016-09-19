#ifndef PIECE_H
#define PIECE_H

class Piece
{
	public:
		//Creates a piece with given owner and type
		Piece(int arg_owner, char arg_type);
		Piece();
		~Piece();
		
		//Returns representation;
		char display();
	
		int getOwner() const;
	private:
		int owner;
		char type;
};

#endif
