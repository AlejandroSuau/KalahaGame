#include "../KalahaGame/classes/player.h"
#include "../KalahaGame/classes/board.h"

struct GameTest : public testing::Test
{
	int* player_holes_;
	int* player_pieces_;

	Player* player_one;
	Player* player_two;
	Board* board;

	int getPlayerHoles();
	int getInitialPlayerPieces();

protected:
	virtual void SetUp();
	virtual void TearDown();
};
