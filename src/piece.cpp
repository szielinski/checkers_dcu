#include<iostream>

#include "piece.h"

Piece::Piece(int arg_owner, char arg_type)
{
	owner = arg_owner;
	type = arg_type;
}

Piece::Piece()
{
	owner = 0;
	type = ' ';
}

Piece::~Piece(){}

char Piece::display()
{
	return type;
}

int Piece::getOwner() const
{
	return owner;
}
