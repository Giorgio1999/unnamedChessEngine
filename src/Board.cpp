#include "Board.h"
#include "Piece.h"

Board::Board() {
	for (auto i = 0;i < 64;i++) {
		this->board[i] = Piece(true, king);
	}
}

Board::~Board() {

}

Piece Board::GetPieceAt(int i) {
	return this->board[i];
}