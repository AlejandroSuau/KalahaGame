#pragma once

class Hole
{
public:
	Hole();
	Hole(const int pieces_number);

	bool isEmpty();
	void addPieces(const int quantity);
	int removeAllPieces();
	void removePieces(const int quantity);
	int getPiecesNumber() const;
	int operator+(Hole h);

protected:
	int pieces_number_;
};
