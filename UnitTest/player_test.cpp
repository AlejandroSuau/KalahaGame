#include "pch.h"
#include "../KalahaGame/classes/player.h"

#include <stdio.h>

struct PlayerTest : public testing::Test
{
	int holes_num;
	int pieces;
	Player* player;

	void SetUp() {
		holes_num = 6;
		pieces = 36;
		std::string player_name = "Alejandro";
		player = new Player(player_name, holes_num, pieces);
	}

	void TearDown() {
		delete player;
	}
};

TEST_F(PlayerTest, PlayerRemoveAllPiecesFromHole)
{
	int hole_idx = 0;
	int player_pieces_before = player->getPieces();
	int removed_pieces = player->removeAllPiecesFromHole(hole_idx);
	
	ASSERT_TRUE(player->getHole(hole_idx).isEmpty());
	
	int player_pieces_after = player->getPieces();
	ASSERT_EQ(player_pieces_before - removed_pieces, player_pieces_after);
}

TEST_F(PlayerTest, PlayerAddPiecesToHole)
{
	int hole_idx = 0;
	int adding_pieces = 5;
	int hole_pieces_before = player->getHole(hole_idx).getPiecesNumber();

	player->addPiecesToHole(hole_idx, adding_pieces);

	int hole_pieces_after = player->getHole(hole_idx).getPiecesNumber();
	ASSERT_EQ(hole_pieces_after - hole_pieces_before, adding_pieces);
}

TEST_F(PlayerTest, PlayerAddAllHolePiecesToBank)
{
	player->addAllHolePiecesToBank();
	ASSERT_EQ(player->getPieces(), 0);
	ASSERT_EQ(player->getBank()->getPiecesNumber(), pieces);
}