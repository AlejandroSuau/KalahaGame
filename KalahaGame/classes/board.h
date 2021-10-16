#pragma once

#include <iostream>
#include "player.h"
#include "pieces_mover.h"

class Board
{
	Player* player_one_;
	Player* player_two_;
	Player* active_player;
	PiecesMover* pieces_mover;

public:
	Board(Player* player_one, Player* player_two);
	~Board();

	void startGame();
	void printBoard();
	void printPlayerTurnHeader();
	void playTurn();
	int getPlayerHoleChoice() const;
	bool isValidPlayerHoleChoice(const int hole_choice) const;
	PiecesMover* getPiecesMover() const;

	Player* getActivePlayer() const;
	void switchActivePlayer();
	void switchPlayer(Player*& player);
	bool isActivePlayer(Player* player) const;
	bool isGameEnd();
	void processGameEnd();
	void addAllPlayerHolePiecesToBank();
	void printWinner();
};

