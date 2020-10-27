#include <iostream>
#include <fstream>
#include "gameboard.hh"

int main() {
    GameBoard board("gameoflife.dat");
    board.run();
}