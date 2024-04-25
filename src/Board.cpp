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
	for (int y = 0;y < 8;y++) {
		for (int x = 0;x < 8;x++) {
			boardString += std::to_string(GetPieceAt(x, y).pieceType);
		}
		boardString += "\n";
	}
	boardString += "\n";
	for (int y = 0;y < 8;y++) {
		for (int x = 0;x < 8;x++) {
			boardString += std::to_string(GetPieceAt(x, y).color);
		}
		boardString += "\n";
	}
	boardString += "\n";
	for (int i = 0;i < 64;i++) {
		boardString += std::to_string(GetPieceAt(i).pieceType);
	}
	boardString += "\n";
	return boardString;
}

void Board::MakeMove(Move move) {
	gameHistory.push_back(board);								//Store position in game history
	Piece piece = GetPieceAt(move.startCoord);
	SetPieceAt(move.startCoord, Piece());
	piece.hasMoved = true;
	if (move.convertTo != none) {
		piece.pieceType = move.convertTo;
	}
	if (move == Str2Move("e1g1")) {
		SetPieceAt(Str2Coord("g1"), piece);
		Piece rook = GetPieceAt(Str2Coord("h1"));
		SetPieceAt(Str2Coord("h1"), Piece());
		SetPieceAt(Str2Coord("f1"), rook);
	}
	else if (move == Str2Move("e1c1")) {
		SetPieceAt(Str2Coord("c1"), piece);
		Piece rook = GetPieceAt(Str2Coord("a1"));
		SetPieceAt(Str2Coord("a1"), Piece());
		SetPieceAt(Str2Coord("d1"), rook);
	}
	else if (move == Str2Move("e8g8")) {
		SetPieceAt(Str2Coord("g8"), piece);
		Piece rook = GetPieceAt(Str2Coord("h8"));
		SetPieceAt(Str2Coord("h8"), Piece());
		SetPieceAt(Str2Coord("f8"), rook);
	}
	else if (move == Str2Move("e8c8")) {
		SetPieceAt(Str2Coord("c8"), piece);
		Piece rook = GetPieceAt(Str2Coord("a8"));
		SetPieceAt(Str2Coord("a8"), Piece());
		SetPieceAt(Str2Coord("d8"), rook);
	}
	else {
		SetPieceAt(move.targetCoord, piece);
	}
}

void Board::UndoLastMove() {
	board = gameHistory.back();
	gameHistory.pop_back();
}
