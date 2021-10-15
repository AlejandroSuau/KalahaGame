// KalahaGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "classes/hole.hpp"

int main()
{
    // Creating a hole to default constructor.
    Hole h1;

    Hole* h2 = new Hole;

    // Creating a hole using constructor.
    Hole h(2);

    std::cout << "Hello World! " << h1.getPiecesNumber() << h2->getPiecesNumber() << "!\n";
}

