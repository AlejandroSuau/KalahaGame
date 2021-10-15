#include "pieces_mover.h"

#include "board.h"
#include "player.h"

void PiecesMover::move(const int starting_hole_idx, int pieces_quantity)
{
	switch_active_player_after_turn = true;

	bool is_last_piece;
	int player_holes_num = moving_player->getHolesNum();
	int current_hole_idx = starting_hole_idx;
	while (pieces_quantity > 0) {
		is_last_piece = (pieces_quantity == 1) ? true : false;

		if (current_hole_idx < player_holes_num) {
			placePieceOnHole(current_hole_idx, is_last_piece);
		}
		else if (current_hole_idx == player_holes_num && isMovingPlayerTurn()) {
			placePieceOnBank(is_last_piece);
		}
		else {
			current_hole_idx = 0;
			board_->switchPlayer(moving_player);
			continue;
		}

		pieces_quantity--;
		current_hole_idx++;
	}
}

void PiecesMover::placePieceOnHole(const int hole_idx, const bool is_last_piece)
{
	bool is_hole_empty = moving_player->isHoleEmpty(hole_idx);
	if (is_hole_empty && is_last_piece && isMovingPlayerTurn()) {
		board_->switchPlayer(moving_player);
		int enemy_hole_idx = moving_player->getHolesNum() - hole_idx - 1;
		int enemy_hole_pieces = moving_player->removeAllPiecesFromHole(enemy_hole_idx);
		printf("\nCongratulations! you've stolen %i pieces from %i hole.\n",
				enemy_hole_pieces, enemy_hole_idx);
		board_->switchPlayer(moving_player);

		moving_player->addPiecesToBank(enemy_hole_pieces + 1);
	}
	else {
		moving_player->addPiecesToHole(hole_idx, 1);
	}
}

void PiecesMover::placePieceOnBank(const bool is_last_piece)
{
	moving_player->addPiecesToBank(1);
	if (is_last_piece) {
		printf("\nCongratulations! you've got an extra turn by ending last piece inside bank.\n");
		switch_active_player_after_turn = false;
	}
}

bool PiecesMover::isMovingPlayerTurn()
{
	return board_->isActivePlayer(moving_player);
}

PiecesMover::PiecesMover(Board* board)
{
	board_ = board;
	moving_player = board_->getActivePlayer();
	switch_active_player_after_turn = true;
}

PiecesMover::~PiecesMover()
{
	
}

void PiecesMover::processPlayerChoice(int hole_idx)
{
	moving_player = board_->getActivePlayer();
	int pieces_to_place = moving_player->removeAllPiecesFromHole(hole_idx);

	hole_idx++;
	move(hole_idx, pieces_to_place);
}

bool PiecesMover::getSwitchActivePlayerAfterTurn()
{
	return switch_active_player_after_turn;
}
