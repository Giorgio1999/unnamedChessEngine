#include "Piece.h"

Piece::Piece() {
	this->color = true;
	this->pieceType = none;
};

Piece::Piece(bool _color, PieceType _pieceType) {
	this->color = _color;
	this->pieceType = _pieceType;
}

PieceList::PieceList() {
	for (auto i = 0;i < 64;i++) {
		pieces[i] = Piece();
	}
}