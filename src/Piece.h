#pragma once

//This is the piece struct. Each piece has a type and nothing else so far
enum PieceType{none,pawn,knight,bishop,rook,queen,king};

struct Piece
{
	bool color;
	bool isPinned = false;
	bool hasMoved = false;
	bool isGhost = false;
	PieceType pieceType;
	
	Piece();
	Piece(bool _color, PieceType _pieceType);

};

struct PieceList {
	Piece pieces[64];
	bool whiteToMove = true;
	bool whiteQueensideCastleRight = false;
	bool whiteKingsideCastleRight = false;
	bool blackQueensideCastleRight = false;
	bool blackKingsideCastleRight = false;
	bool isEnpassantable = false;
};

