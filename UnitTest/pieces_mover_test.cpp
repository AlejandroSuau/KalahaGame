#include "pch.h"
#include "game_test.h"
#include "../KalahaGame/classes/pieces_mover.h"

struct PiecesMoverTest : public GameTest
{
	PiecesMover* pieces_mover;

	void SetUp()
	{
		GameTest::SetUp();
		pieces_mover = board->getPiecesMover();
	}

	void TearDown()
	{
		GameTest::TearDown();
	}
};

TEST_F(PiecesMoverTest, PiecesMoverProcessPlayerChoice)
{
	// Moving last piece from game beginning.

	int hole_idx = getPlayerHoles() - 1;
	int hole_pieces = player_one->getHole(hole_idx).getPiecesNumber();
	pieces_mover->processPlayerChoice(hole_idx);

	ASSERT_TRUE(player_one->getHole(hole_idx).isEmpty());
	ASSERT_EQ(player_one->getPieces(), getInitialPlayerPieces() - hole_pieces);
	ASSERT_EQ(player_one->getBank()->getPiecesNumber(), 1);

	int player_two_expected_pieces = getInitialPlayerPieces() + hole_pieces - 1;
	ASSERT_EQ(player_two->getPieces(), player_two_expected_pieces);
	
	ASSERT_TRUE(pieces_mover->getSwitchActivePlayerAfterTurn());
}

TEST_F(PiecesMoverTest, PiecesMoverEndsPieceOnBank)
{
	// Moving first piece from game beginning.

	int hole_idx = 0;
	int hole_pieces = player_one->getHole(hole_idx).getPiecesNumber();
	pieces_mover->processPlayerChoice(hole_idx);

	ASSERT_TRUE(player_one->getHole(hole_idx).isEmpty());
	ASSERT_EQ(player_one->getPieces(), getInitialPlayerPieces() - 1);
	ASSERT_EQ(player_one->getBank()->getPiecesNumber(), 1);
	
	ASSERT_FALSE(pieces_mover->getSwitchActivePlayerAfterTurn());
}

TEST_F(PiecesMoverTest, PiecesMoverEndsPieceOnEmptyHole)
{
	int holes_number = player_one->getHolesNum();
	int removing_hole_pieces = 5;
	for (int i = 0; i < holes_number; i++) {
		player_one->removeAllPiecesFromHole(i);
		player_one->addPiecesToHole(i, 1);

		player_two->removeAllPiecesFromHole(i);
		player_two->addPiecesToHole(i, 1);
	}
	
	ASSERT_TRUE(player_one->getPieces(), 6);
	ASSERT_TRUE(player_two->getPieces(), 6);
	
	//    1  1  1  1  1  1
	// 0					0
	//	  1  1  1  1  1  1

	ASSERT_EQ(board->getActivePlayer(), player_one);
	pieces_mover->processPlayerChoice(1);

	//    1  1  1  1  1  1
	// 0					0
	//	  1  0  2  1  1  1

	ASSERT_EQ(board->getActivePlayer(), player_one);
	pieces_mover->processPlayerChoice(0);

	//    1  0  1  1  1  1
	// 0					2
	//	  0  0  2  1  1  1

	ASSERT_TRUE(player_one->getBank()->getPiecesNumber(), 2);
	ASSERT_TRUE(player_one->getPieces(), 5);
	ASSERT_EQ(player_one->getHole(1).getPiecesNumber(), 0);

	ASSERT_TRUE(player_two->getPieces(), 5);
	ASSERT_EQ(player_two->getHole(4).getPiecesNumber(), 0);
}