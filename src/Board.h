#pragma once
#include "Piece.h"
#include "Move.h"
#include <string>
#include <list>

//This is the board class responsible for representing the chessboard
class Board
{
public:
	Board();
	~Board();
	Piece GetPieceAt(int i);							//Retrieve piece at index.
	Piece GetPieceAt(int column, int row);				//Retrieve piece atcolumn, row
	Piece GetPieceAt(Coord coord);						//Retrieve piece at Coord
	void SetPieceAt(int i, Piece piece);				//set piece at index
	void SetPieceAt(int column, int row, Piece piece);	//set piece at column, row
	void SetPieceAt(Coord coord, Piece piece);			//set piece at coord
	void Clear();										//Clears board (places white non pieces)
	void SetPosition(PieceList pieces);					//Sets the whole board to a given PieceList
	std::string ShowBoard();							//Debugging function to get string of simple board representation
	void MakeMove(Move move);							//Make a move, will make any move not only legal moves
	void UndoLastMove();								//Revert to previous position
	void BustGhosts();									//Removes Ghosts
	void RemoveAllCastleRights(bool color);				//Sets all castle rights to false of given color

private:
	PieceList board;
	std::list<PieceList> gameHistory;
};
