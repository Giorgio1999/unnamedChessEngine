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

