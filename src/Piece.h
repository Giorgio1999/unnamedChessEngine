#pragma once
#include <string>

//This is the piece struct. Each piece has a type and nothing else so far

enum PieceType{none,pawn,knight,bishop,rook,queen,king};	//Piece types including none for empty squares
const std::string types = "-pnbrqk";

struct Piece
{
	bool color;				//Color of piece
	bool isPinned = false;	//flag for pinned pieces (?)
	bool hasMoved = false;	//flag for if piece has moved, maybe for castling and double pawn pushes (?)
	bool isGhost = false;	//flag for the square pawns can be captured by en passant (?)
	PieceType pieceType;	
	
	Piece();
	Piece(bool _color, PieceType _pieceType);	//simple constructor

};

//slightly misleading name. its actually a struct that holds a position. But can be used for holding up to 64 pieces i guess
struct PieceList {
	Piece pieces[64];
	bool whiteToMove = true;					//who can move in this position
	bool whiteQueensideCastleRight = false;		//flags for castling (?)
	bool whiteKingsideCastleRight = false;
	bool blackQueensideCastleRight = false;
	bool blackKingsideCastleRight = false;
	bool isEnpassantable = false;				//flag if en passant is possible in position

	PieceList();
};

std::string PieceType2Str(PieceType type);

