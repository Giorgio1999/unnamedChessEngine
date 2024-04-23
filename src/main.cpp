#include "Board.h"
#include "UciHandler.h"
#include <iostream>


int main() {
	//Listen();
	Board board = Board();
	std::cout << board.GetPieceAt(0).pieceType;
	return 0;
}