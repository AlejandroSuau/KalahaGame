#include "pch.h"
#include "../KalahaGame/classes/hole.hpp"


struct HoleTest : public testing::Test
{
	Hole* hole;

	void SetUp() {
		hole = new Hole;
	}

	void TearDown() {
		delete hole;
	}
};

TEST_F(HoleTest, HoleIsEmpty)
{
	ASSERT_TRUE(hole->isEmpty());
}

TEST_F(HoleTest, HoleAddPieces)
{
	int pieces_number = 5;
	hole->addPieces(pieces_number);
	ASSERT_EQ(hole->getPiecesNumber(), pieces_number);
}

TEST_F(HoleTest, HoleRemovePieces)
{
	int pieces_number = 5;
	Hole* hole_filled = new Hole(pieces_number);
	hole_filled->removePieces(pieces_number);
	ASSERT_EQ(hole_filled->getPiecesNumber(), 0);
	delete hole_filled;
}

TEST_F(HoleTest, HoleRemoveAllPieces)
{
	int pieces_number = 5;
	Hole* hole_filled = new Hole(pieces_number);
	ASSERT_EQ(hole_filled->removeAllPieces(), pieces_number);
	ASSERT_EQ(hole_filled->getPiecesNumber(), 0);
}
