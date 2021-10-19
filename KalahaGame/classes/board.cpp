#include "board.h"

Board::Board(Player* player_one, Player* player_two)
{
	player_one_ = player_one;
	player_two_ = player_two;
	active_player = player_one;
	pieces_mover = new PiecesMover(this);
}

Board::~Board()
{
	delete player_one_;
	delete player_two_;
	delete pieces_mover;
}

void Board::startGame()
{
	do {
		printBoard();
		
		std::cout << "\n" << active_player->getName() << " is playing ...\n";
		playTurn();

		if (pieces_mover->getSwitchActivePlayerAfterTurn()) {
			switchActivePlayer();
		}

	} while (!isGameEnd());

	processGameEnd();
}

void Board::printBoard()
{
	switchActivePlayer();
	
	printPlayerBoardHeader(active_player);

	printBoardTopBorder();
	printBoardBlankLine();
	active_player->printHolesLine(true);
	
	printBoardBlankLine();
	printBoardBanksLine();
	printBoardBlankLine();
	
	active_player->printHolesLine();
	printBoardBottomBorder();
	
	printPlayerBoardHeader(active_player);
}

void Board::printBoardTopBorder()
{
	std::cout << " " << std::setw(BOARD_PRINT_LINE_WIDTH - 1) << std::setfill('_') << " ";
}

void Board::printBoardBottomBorder()
{
	std::cout << "\n|" << std::setw(BOARD_PRINT_LINE_WIDTH - 1) << std::setfill('_') << "|";
}

void Board::printBoardBlankLine()
{
	std::cout << "\n|" << std::setw(BOARD_PRINT_LINE_WIDTH - 1) << std::setfill(' ') << "|";
}

void Board::printBoardBanksLine()
{
	std::cout << "\n|  ";
	std::cout << *(active_player->getBank());

	switchActivePlayer();

	int bank_spaces_between = BOARD_PRINT_LINE_WIDTH - 8;
	int bank_pieces = active_player->getBank()->getPiecesNumber();
	if (bank_pieces < 10) {
		bank_spaces_between--;
	}
	std::cout << std::setw(bank_spaces_between) << std::setfill(' ');
	std::cout << *(active_player->getBank()) << "  |";
}

void Board::printPlayerBoardHeader(Player* player)
{
	int half_string_length = player->getName().length() / 2;
	int half_output_width = BOARD_PRINT_LINE_WIDTH / 2;
	int leading_spaces = half_output_width - half_string_length;

	std::cout << "\n\n" << std::setw(leading_spaces);
	std::cout << std::setfill(' ') << "" << player->getName() << "\n";
}

void Board::playTurn()
{
	int hole_choice = getPlayerHoleChoice();
	pieces_mover->processPlayerChoice(hole_choice);
}

int Board::getPlayerHoleChoice() const
{
	int hole_choice;
	bool valid_hole_choice = false;
	while (!valid_hole_choice) {
		std::cout << "\n* Enter a hole index:";
		std::cin >> hole_choice;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (isValidPlayerHoleChoice(hole_choice)) {
			valid_hole_choice = true;
		}
		else {
			std::cout << "\nError: Please enter a valid hole number";
		}

		std::cout << "\n";
		
		--hole_choice;
	}

	return hole_choice;
}

bool Board::isValidPlayerHoleChoice(const int hole_choice) const
{
	int hole_idx = hole_choice - 1;
	bool is_valid_idx = hole_idx >= 0 && hole_idx < active_player->getHolesNum();
	bool is_hole_empty = active_player->isHoleEmpty(hole_idx);
	
	return is_valid_idx && !is_hole_empty;
}

PiecesMover* Board::getPiecesMover() const
{
	return pieces_mover;
}

Player* Board::getActivePlayer() const
{
	return active_player;
}

void Board::switchActivePlayer()
{
	switchPlayer(active_player);
}

void Board::switchPlayer(Player*& player)
{
	if (player == player_one_) {
		player = player_two_;
	} else {
		player = player_one_;
	}
}

bool Board::isActivePlayer(Player* player) const
{
	return active_player == player;
}

bool Board::isGameEnd()
{
	return player_one_->getPieces() == 0 || player_two_->getPieces() == 0;
}

void Board::processGameEnd()
{
	addAllPlayerHolePiecesToBank();
	printWinner();
}

void Board::addAllPlayerHolePiecesToBank()
{
	player_one_->addAllHolePiecesToBank();
	player_two_->addAllHolePiecesToBank();
}

void Board::printWinner()
{
	int player_one_points = player_one_->getBank()->getPiecesNumber();
	int player_two_points = player_two_->getBank()->getPiecesNumber();

	if (player_one_points > player_two_points) {
		std::cout << "\nPlayer one WINS!";
	}
	else if (player_one_points == player_two_points) {
		std::cout << "\nThis game ends in TIE!";
	}
	else {
		std::cout << "\nPlayer two WINS!";
	}
	
	printf("\n%s: %i points", player_one_->getName().c_str(), player_one_points);
	printf("\n%s: %i points\n", player_two_->getName().c_str(), player_two_points);
}
