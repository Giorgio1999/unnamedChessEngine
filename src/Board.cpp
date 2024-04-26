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
	board.whiteKingsideCastleRight = pieces.whiteKingsideCastleRight;
	board.whiteQueensideCastleRight = pieces.whiteQueensideCastleRight;
	board.blackKingsideCastleRight = pieces.blackKingsideCastleRight;
	board.blackQueensideCastleRight = pieces.blackQueensideCastleRight;
	board.isEnpassantable = pieces.isEnpassantable;
	board.whiteToMove = pieces.whiteToMove;
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
	for (int y = 0;y < 8;y++) {
		for (int x = 0;x < 8;x++) {
			boardString += std::to_string(GetPieceAt(x, y).isGhost);
		}
		boardString += "\n";
	}
	boardString += "\n";
	return boardString;
}

void Board::MakeMove(Move move) {
	gameHistory.push_back(board);								//Store position in game history
	Piece piece = GetPieceAt(move.startCoord);
	if (GetPieceAt(move.targetCoord).isGhost) {
		int sign = board.whiteToMove ? 1 : -1;
		Piece ghoster = Piece();
		SetPieceAt(Coord(move.targetCoord.x, move.targetCoord.y + sign), ghoster);
	}
	BustGhosts();
	SetPieceAt(move.startCoord, Piece());
	if (piece.pieceType == pawn && std::abs(move.startCoord.y-move.targetCoord.y)>1) {	//Double pawn pushes
		Piece ghost = Piece();
		ghost.isGhost = true;
		ghost.color = board.whiteToMove;
		int sign = board.whiteToMove ? 1 : -1;
		SetPieceAt(Coord(move.targetCoord.x, move.targetCoord.y + sign), ghost);
		board.isEnpassantable = true;
	}
	if (move.convertTo != none) {	//Pawn promotion
		piece.pieceType = move.convertTo;
	}
	if (move == Str2Move("e1g1") && board.whiteKingsideCastleRight && board.whiteToMove) {	//Castling
		SetPieceAt(Str2Coord("g1"), piece);
		Piece rook = GetPieceAt(Str2Coord("h1"));
		SetPieceAt(Str2Coord("h1"), Piece());
		SetPieceAt(Str2Coord("f1"), rook);
		RemoveAllCastleRights(true);
	}
	else if (move == Str2Move("e1c1") && board.whiteQueensideCastleRight && board.whiteToMove) {
		SetPieceAt(Str2Coord("c1"), piece);
		Piece rook = GetPieceAt(Str2Coord("a1"));
		SetPieceAt(Str2Coord("a1"), Piece());
		SetPieceAt(Str2Coord("d1"), rook);
		RemoveAllCastleRights(true);
	}
	else if (move == Str2Move("e8g8") && board.blackKingsideCastleRight && !board.whiteToMove) {
		SetPieceAt(Str2Coord("g8"), piece);
		Piece rook = GetPieceAt(Str2Coord("h8"));
		SetPieceAt(Str2Coord("h8"), Piece());
		SetPieceAt(Str2Coord("f8"), rook);
		RemoveAllCastleRights(false);
	}
	else if (move == Str2Move("e8c8") && board.blackQueensideCastleRight && !board.whiteToMove) {
		SetPieceAt(Str2Coord("c8"), piece);
		Piece rook = GetPieceAt(Str2Coord("a8"));
		SetPieceAt(Str2Coord("a8"), Piece());
		SetPieceAt(Str2Coord("d8"), rook);
		RemoveAllCastleRights(false);
	}
	else {	//Default move making
		SetPieceAt(move.targetCoord, piece);
		if (piece.pieceType == rook && !piece.hasMoved) {
			if (move.startCoord.x == 0) {
				if (board.whiteToMove) {
					board.whiteKingsideCastleRight = false;
				}
				else {
					board.blackKingsideCastleRight = false;
				}
			}
			if (move.startCoord.x == 7) {
				if (board.whiteToMove) {
					board.whiteQueensideCastleRight = false;
				}
				else {
					board.blackQueensideCastleRight = false;
				}
			}
		}
		if (piece.pieceType == king && !piece.hasMoved) {
			if (board.whiteToMove) {
				board.whiteKingsideCastleRight = false;
				board.whiteQueensideCastleRight = false;
			}
			else {
				board.blackKingsideCastleRight = false;
				board.blackQueensideCastleRight = false;
			}
		}
	}
	board.whiteToMove = !board.whiteToMove;
	piece.hasMoved = true;
}

void Board::UndoLastMove() {
	board = gameHistory.back();
	gameHistory.pop_back();
}

void Board::BustGhosts() {
	for (int i = 0;i < 64;i++) {
		Piece current = GetPieceAt(i);
		current.isGhost = false;
		SetPieceAt(i,current);
	}
	board.isEnpassantable = false;
}

void Board::RemoveAllCastleRights(bool color) {
	if (color) {
		board.whiteKingsideCastleRight = false;
		board.whiteQueensideCastleRight = false;
	}
	else {
		board.blackKingsideCastleRight = false;
		board.blackQueensideCastleRight = false;
	}
}

bool Board::WhiteToMove() {
	return board.whiteToMove;
}

int Board::GetCastleRights(bool color) {
	int res = 0;
	if (color) {
		if (board.whiteKingsideCastleRight) {
			res = 1;
		}
		else if (board.whiteQueensideCastleRight) {
			res = 2;
		}
		if (board.whiteKingsideCastleRight && board.whiteQueensideCastleRight) {
			res = 3;
		}
	}
	else {
		if (board.blackKingsideCastleRight) {
			res = 1;
		}
		else if (board.blackQueensideCastleRight) {
			res = 2;
		}
		if (board.blackKingsideCastleRight && board.blackQueensideCastleRight) {
			res = 3;
		}
	}
	return res;
}