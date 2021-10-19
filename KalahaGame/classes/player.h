#pragma once

#include <iostream>
#include <iomanip>
#include <array>

#include "hole.hpp"
#include "bank.hpp"

constexpr int PLAYER_HOLES = 6;

class Player
{
	std::string name_;
	int holes_num_;
	int pieces_;
	Hole* holes;
	Bank* bank;

	void initializeHoles();

public:
	Player(const std::string name, const int holes_num, const int pieces);
	~Player();

	bool isHoleEmpty(const int hole_idx) const;
	int removeAllPiecesFromHole(const int hole_idx);
	void addPiecesToHole(const int hole_idx, const int quantity);
	void addPiecesToBank(const int quantity);
	void addAllHolePiecesToBank();

	void printHolesLine(bool inverse = false);

	std::string getName() const;
	int getHolesNum() const;
	int getPieces() const;
	Hole getHole(int hole_idx) const;
	Hole* getHoles() const;
	Bank* getBank() const;
};

