#include "player.h"

Player::Player(const std::string name, const int holes_num, const int pieces)
{
	name_ = name;
	holes_num_ = holes_num;
	pieces_ = pieces;
	bank = new Bank;

	initializeHoles();
}

Player::~Player()
{
	delete bank;
	delete[] holes;
}

bool Player::isHoleEmpty(const int hole_idx) const
{
	return holes[hole_idx].isEmpty();
}

int Player::removeAllPiecesFromHole(const int hole_idx)
{
	int removed_pieces = holes[hole_idx].removeAllPieces();
	pieces_ -= removed_pieces;
	return removed_pieces;
}

void Player::addPiecesToHole(const int hole_idx, const int quantity)
{
	pieces_ += quantity;
	holes[hole_idx].addPieces(quantity);
}

void Player::addPiecesToBank(const int quantity)
{
	bank->addPieces(quantity);
}

void Player::addAllHolePiecesToBank()
{
	if (pieces_ == 0) return;

	int total_removed_pieces = 0;
	for (int i = 0; i < holes_num_; i++) {
		total_removed_pieces += holes[i].removeAllPieces();
	}
	addPiecesToBank(total_removed_pieces);
	pieces_ -= total_removed_pieces;
}

void Player::initializeHoles()
{
	holes = new Hole[holes_num_];
	int pieces_per_hole = pieces_ / holes_num_;
	for (int i = 0; i < holes_num_; i++) {
		holes[i] = Hole(pieces_per_hole);
	}
}

void Player::printHolesLine(bool inverse)
{
	std::cout << "\n|";
	std::cout << std::setw(6) << std::setfill(' ');
	std::cout << "";

	int start, end;
	if (inverse) {
		start = (holes_num_ - 1) *-1;
		end = 1;
	}
	else {
		start = 0;
		end = holes_num_;
	}

	for (int i = start; i < end; i++) {
		std::cout << holes[abs(i)] << "  ";
	}

	std::cout << std::setw(5) << std::setfill(' ') << "|";
}

std::string Player::getName() const
{
	return name_;
}

int Player::getHolesNum() const
{
	return holes_num_;
}

int Player::getPieces() const
{
	return pieces_;
}

Hole Player::getHole(int hole_idx) const
{
	return holes[hole_idx];
}

Hole* Player::getHoles() const
{
	return holes;
}

Bank* Player::getBank() const
{
	return bank;
}
