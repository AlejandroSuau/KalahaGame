#include "pch.h"
#include "game_test.h"

int GameTest::getPlayerHoles()
{
	return *player_holes_;
}

int GameTest::getInitialPlayerPieces()
{
	return *player_pieces_;
}

void GameTest::SetUp()
{
	player_holes_ = new int(6);
	player_pieces_ = new int(getPlayerHoles() * 6);

	player_one = new Player("Alejandro", getPlayerHoles(), getInitialPlayerPieces());
	player_two = new Player("Sara", getPlayerHoles(), getInitialPlayerPieces());
	board = new Board(player_one, player_two);
}

void GameTest::TearDown()
{
	delete board;
	delete player_holes_;
	delete player_pieces_;
}
