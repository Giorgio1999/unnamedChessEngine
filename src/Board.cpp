#include "Board.h"
#include "Piece.h"
#include <string>

Board::Board() {
	for (auto i = 0; i < 64; i++) {
		this->board[i] = Piece();
	}
}

Board::~Board() {

}

void Board::Clear() {
	Piece clearPiece = Piece();
	for (auto i = 0; i < 64; i++) {
		board[i] = clearPiece;
	}
}

Piece Board::GetPieceAt(int i) {
	return this->board[i];
}

Piece Board::GetPieceAt(int row, int column) {
	return GetPieceAt(row * 8 + column);
}

void Board::SetPosition(PieceList pieces) {
	for (auto i = 0; i < 64; i++) {
		board[i] = pieces.pieces[i];
	}
}

std::string Board::ShowBoard() {
	std::string boardString = "";
	for (int i = 7;i >= 0;i--) {
		for (auto j = 0;j < 8;j++) {
			boardString += GetPieceAt(i, j).color;
		}
		boardString += "\n";
	}
	return boardString;
}