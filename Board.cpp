#include "Board.h"
#include "Piece.h"

Board::Board() {
	for (auto i = 0;i < 64;i++) {
		this->board[i] = Piece(false, none);
	}
}

Board::~Board() {

}