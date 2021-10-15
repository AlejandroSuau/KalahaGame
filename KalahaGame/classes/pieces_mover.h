#pragma once

class Player;
class Board;

class PiecesMover
{
	Board* board_;
	Player* moving_player;
	bool switch_active_player_after_turn;

	void move(const int starting_hole_idx, int pieces_quantity);

	void placePieceOnHole(const int hole_idx, const bool is_last_piece);
	void placePieceOnBank(const bool is_last_piece);
	bool isMovingPlayerTurn();

public:
	PiecesMover(Board* board);
	~PiecesMover();

	void processPlayerChoice(int hole_idx);
	bool getSwitchActivePlayerAfterTurn();
};

