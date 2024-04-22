#include "Piece.h"

Piece::Piece() {
	this->color = true;
	this->pieceType = none;
};

Piece::Piece(bool _color, PieceType _pieceType) {
	this->color = _color;
	this->pieceType = _pieceType;
}