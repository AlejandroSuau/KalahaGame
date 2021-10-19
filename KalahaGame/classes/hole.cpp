#include "hole.hpp"

Hole::Hole() 
{
	pieces_number_ = 0;
}

Hole::Hole(int pieces_number) 
{
	pieces_number_ = pieces_number;
}

bool Hole::isEmpty()
{
	return pieces_number_ == 0;
}

void Hole::addPieces(const int quantity)
{
	pieces_number_ += quantity;
}

int Hole::removeAllPieces()
{
	int current_pieces = pieces_number_;
	pieces_number_ = 0;
	return current_pieces;
}

void Hole::removePieces(const int quantity)
{
	pieces_number_ = 0;
}

int Hole::operator+(Hole h) 
{
	return pieces_number_ + h.getPiecesNumber();
}

int Hole::getPiecesNumber() const 
{
	return pieces_number_;
}


std::ostream& operator<< (std::ostream& out, const Hole& h)
{
	if (h.pieces_number_ < 10) {
		out << " ";
	}
	out << h.pieces_number_;
	return out;
}