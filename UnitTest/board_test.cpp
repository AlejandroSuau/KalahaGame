#include "pch.h"
#include "game_test.h"

struct BoardTest : public GameTest {};

TEST_F(BoardTest, BoardIsActivePlayer)
{
	ASSERT_TRUE(board->getActivePlayer(), player_one);
}

TEST_F(BoardTest, BoardSwitchPlayer)
{
	board->switchPlayer(player_one);
	ASSERT_EQ(player_one, player_two);
}

TEST_F(BoardTest, BoardSwitchActivePlayer)
{
	ASSERT_EQ(board->getActivePlayer(), player_one);
	board->switchActivePlayer();
	ASSERT_EQ(board->getActivePlayer(), player_two);
}

TEST_F(BoardTest, BoardIsValidPlayerHoleChoice)
{
	int valid_choice = 1;
	ASSERT_TRUE(board->isValidPlayerHoleChoice(valid_choice));
	ASSERT_TRUE(board->isValidPlayerHoleChoice(getPlayerHoles()));

	int invalid_choice = 0;
	ASSERT_FALSE(board->isValidPlayerHoleChoice(invalid_choice));
	ASSERT_FALSE(board->isValidPlayerHoleChoice(getPlayerHoles() + 1));
}

TEST_F(BoardTest, BoardAddAllPlayerHolePiecesToBank)
{
	ASSERT_EQ(player_one->getPieces(), getInitialPlayerPieces());
	ASSERT_EQ(player_two->getPieces(), getInitialPlayerPieces());

	board->addAllPlayerHolePiecesToBank();

	ASSERT_EQ(player_one->getPieces(), 0);
	ASSERT_EQ(player_two->getPieces(), 0);
	ASSERT_EQ(player_one->getBank()->getPiecesNumber(), getInitialPlayerPieces());
	ASSERT_EQ(player_two->getBank()->getPiecesNumber(), getInitialPlayerPieces());
}

TEST_F(BoardTest, BoardIsGameEnd)
{
	board->addAllPlayerHolePiecesToBank();

	ASSERT_EQ(player_one->getPieces(), 0);
	ASSERT_EQ(player_two->getPieces(), 0);

	ASSERT_TRUE(board->isGameEnd());
}