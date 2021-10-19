// TheGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "../KalahaGame/classes/board.h"
#include "../KalahaGame/classes/player.h"

int main()
{
    int player_holes = 6;
    int player_pieces = 36;
    Player* player_one = new Player("Alejandro", player_holes, player_pieces);
    Player* player_two = new Player("Sara", player_holes, player_pieces);
    Board* board = new Board(player_one, player_two);
    board->startGame();

    return 0;
}

