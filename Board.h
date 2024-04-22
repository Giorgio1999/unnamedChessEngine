#pragma once
#include "Piece.h"

//This is the board class responsible for representing the chessboard
class Board
{
public:
	Board();
	~Board();

private:
	Piece board[64];
};
