#pragma once

#include <iostream>
#include <iomanip>

#include "player.h"
#include "pieces_mover.h"

constexpr int BOARD_PRINT_LINE_WIDTH = 36;

class Board
{
	Player* player_one_;
	Player* player_two_;
	Player* active_player;
	PiecesMover* pieces_mover;

	void printBoardTopBorder();
	void printBoardBottomBorder();
	void printBoardBlankLine();
	void printBoardBanksLine();
	void printPlayerBoardHeader(Player* player);


public:
	Board(Player* player_one, Player* player_two);
	~Board();

	void startGame();
	void printBoard();
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

