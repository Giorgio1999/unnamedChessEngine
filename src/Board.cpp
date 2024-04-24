#include "Board.h"
#include "Piece.h"
#include <string>

Board::Board() {
	for (auto i = 0; i < 64; i++) {
		this->board.pieces[i] = Piece();
	}
}

Board::~Board() {

}

void Board::Clear() {
	Piece clearPiece = Piece();
	for (auto i = 0; i < 64; i++) {
		board.pieces[i] = clearPiece;
	}
}

Piece Board::GetPieceAt(int i) {
	return this->board.pieces[i];
}

Piece Board::GetPieceAt(int column, int row) {
	return GetPieceAt(row * 8 + column);
}

Piece Board::GetPieceAt(Coord coord) {
	return GetPieceAt(coord.x, coord.y);
}

void Board::SetPieceAt(int i, Piece piece) {
	board.pieces[i] = piece;
}

void Board::SetPieceAt(int column, int row, Piece piece) {
	SetPieceAt(row * 8 + column, piece);
}

void Board::SetPieceAt(Coord coord, Piece piece) {
	SetPieceAt(coord.x, coord.y, piece);
}

void Board::SetPosition(PieceList pieces) {
	for (auto i = 0; i < 64; i++) {
		board.pieces[i] = pieces.pieces[i];
	}
}

std::string Board::ShowBoard() {
	std::string boardString = "";
	for (int i = 7;i >= 0;i--) {
		for (auto j = 0;j < 8;j++) {
			boardString += std::to_string(GetPieceAt(j, i).pieceType);
		}
		boardString += "\n";
	}
	return boardString;
}

void Board::MakeMove(Move move) {
	gameHistory.push_back(board);								//Store position in game history
	SetPieceAt(move.targetCoord, GetPieceAt(move.startCoord));
	SetPieceAt(move.startCoord, Piece());
}

void Board::UndoLastMove() {
	board = gameHistory.back();
	gameHistory.pop_back();
}
