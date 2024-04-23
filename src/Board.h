#pragma once
#include "Piece.h"
#include <string>

//This is the board class responsible for representing the chessboard
class Board
{
public:
	Board();
	~Board();
	Piece GetPieceAt(int i);				//Retrieve piece at index.
	Piece GetPieceAt(int row, int column);	//Retrive piece at row,column
	void Clear();							//Clears board (places white non pieces)
	void SetPosition(PieceList pieces);		//Sets the whole board to a given PieceList
	std::string ShowBoard();				//Debugging function to get string of simple board representation

private:
	Piece board[64];
};
