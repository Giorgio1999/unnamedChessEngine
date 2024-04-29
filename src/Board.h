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
	bool WhiteToMove();									//Return white to move
	int GetCastleRights(bool color);					//Returns an integer which encodes the castle rights for the given color: 0=none, 1=queen, 2=king, 3=both
	void UpdateCheckLines();							//Updates the list of lines along which the enemy sees the king
	void UpdateCheckLines(bool kingColor);				//Overload which specifies the color. used in legal move gen
	void UpdateCheckLines(bool kingColor, Coord checkCoord);		//This overload can be used to check for castling squares. also in legal move gen
	//These functions directly update check state
	std::list<Coord> GetStraightOfCoords(Coord start, Coord target);	//Return an uninterrupted line of Coords from start (inclusive) to target (exclusive). If there is a blocker an empty line is return. Only possible lines are like a rook, like a bishop
	std::list<Coord> GetKnightChecks(Coord start, Coord target);	//Returns start if knight would reach target
	std::list<Coord> GetDiagonalOfCoords(Coord start, Coord target);	//Returns diagonal. used for bishop and queen
	std::list<Coord> GetPawnChecks(Coord start, Coord target, bool colorOfMover);		//Returns start if pawn can reach target
	//^^
	std::list<std::list<Coord>>& GetCheckLines();
	bool IsCheck(bool color);	//Checks if the player with color is currently in check
	bool GetCheck();

private:
	PieceList board;
	std::vector<PieceList> gameHistory;
	std::list<std::list<Coord>> checkLines;
	bool isCheck = false;			//If player to move is in check
};
