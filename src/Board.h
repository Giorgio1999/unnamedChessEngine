#pragma once
#include "Piece.h"

//This is the board class responsible for representing the chessboard
class Board
{
public:
	Board();
	~Board();
	Piece GetPieceAt(int i);	//Retrieve piece at index. TO DO: retrieve Piece at row,colum

private:
	Piece board[64];
};
