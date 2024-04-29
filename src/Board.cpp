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
	for (int i = 0;i < checkLines.size();i++) {
		std::list<Coord> current = checkLines.back();
		for (int j = 0;j < current.size();j++) {
			boardString += Coord2Str(current.back());
			Coord tmp = current.back();
			current.pop_back();
			current.push_front(tmp);
		}
		checkLines.pop_back();
		checkLines.push_front(current);
		boardString += "\n";
	}

	return boardString;
}

void Board::MakeMove(Move move) {
	gameHistory.push_back(board);								//Store position in game history
	Piece piece = GetPieceAt(move.startCoord);
	piece.hasMoved = true;
	if (piece.pieceType == pawn && GetPieceAt(move.targetCoord).isGhost) {
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
	if (move.convertTo != none) {	//if moves read from console they have converto none, else just leave the piece unchanged
		piece.pieceType = move.convertTo;
	}
	if (move == Move(4,7,6,7) && board.whiteKingsideCastleRight && board.whiteToMove) {	//Castling e1g1
		SetPieceAt(Coord(6,7), piece);	//g1
		Piece rook = GetPieceAt(Coord(7,7));	//h1
		SetPieceAt(Coord(7, 7), Piece());	//h1
		SetPieceAt(Coord(5,7), rook);	//f1
		RemoveAllCastleRights(true);
	}
	else if (move == Move(4,7,2,7) && board.whiteQueensideCastleRight && board.whiteToMove) {	//e1c1
		SetPieceAt(Coord(2,7), piece);	//c1
		Piece rook = GetPieceAt(Coord(0,7));	//a1
		SetPieceAt(Coord(0, 7), Piece());	//a1
		SetPieceAt(Coord(3,7), rook);	//d1
		RemoveAllCastleRights(true);
	}
	else if (move == Move(4,0,6,0) && board.blackKingsideCastleRight && !board.whiteToMove) {	//e8g8
		SetPieceAt(Coord(6,0), piece);	//g8
		Piece rook = GetPieceAt(Coord(7,7));	//h8
		SetPieceAt(Coord(7, 0), Piece());	//h8
		SetPieceAt(Coord(5,0), rook);	//f8
		RemoveAllCastleRights(false);
	}
	else if (move == Move(4,0,2,0) && board.blackQueensideCastleRight && !board.whiteToMove) {	//e8c8
		SetPieceAt(Coord(2,0), piece);	//c8
		Piece rook = GetPieceAt(Coord(0,7));	//a8
		SetPieceAt(Coord(0, 0), Piece());	//a8
		SetPieceAt(Coord(3,0), rook);	//d8
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
	//UpdateCheckLines();
	isCheck = false;
}

void Board::UndoLastMove() {
	board = gameHistory.back();
	gameHistory.pop_back();
}

void Board::BustGhosts() {
	for (auto i = 0;i < 64;i++ ) {
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
	auto res = 0;
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

void Board::UpdateCheckLines() {
	UpdateCheckLines(board.whiteToMove);
}

void Board::UpdateCheckLines(bool kingColor) {
	Coord kingCoord;
	Piece current;
	for (auto i = 0;i < 8;i++) {
		for (auto j = 0;j < 8;j++) {
			current = GetPieceAt(i,j);
			if (current.pieceType == king && current.color == kingColor) {
				kingCoord = Coord(i, j);
			}
		}
	}
	UpdateCheckLines(kingColor, kingCoord);
}

void Board::UpdateCheckLines(bool kingColor, Coord checkCoord) {
	std::list<std::list<Coord>> newCheckLines;
	Piece current;
	for (auto i = 0;i < 8;i++) {
		for (auto j = 0;j < 8;j++) {
			Piece current = GetPieceAt(i, j);
			if (current.color != kingColor) {
				switch (current.pieceType) {
				case rook:
					newCheckLines.push_back(GetStraightOfCoords(Coord(i, j), checkCoord));
					break;
				case bishop:
					newCheckLines.push_back(GetDiagonalOfCoords(Coord(i, j), checkCoord));
					break;
				case queen:
					newCheckLines.push_back(GetStraightOfCoords(Coord(i, j), checkCoord));
					newCheckLines.push_back(GetDiagonalOfCoords(Coord(i, j), checkCoord));
					break;
				case knight:
					newCheckLines.push_back(GetKnightChecks(Coord(i, j), checkCoord));
					break;
				case pawn:
					newCheckLines.push_back(GetPawnChecks(Coord(i, j), checkCoord, current.color));
					break;
				}
			}
		}
	}
	checkLines = newCheckLines;
}

std::list<Coord> Board::GetStraightOfCoords(Coord start, Coord target) {
	std::list<Coord> coordLine;
	auto tempCheck = true;
	if (start.x - target.x == 0) {
		auto sign = start.y < target.y ? 1 : -1;
		auto I = start.y + sign;
		//coordLine.push_back(start);
		while (I != target.y) {
			if (GetPieceAt(start.x, I).pieceType != none) {
				tempCheck = false;
			}
			//coordLine.push_back(Coord(start.x, I));
			I += sign;
		}
		if (tempCheck) {
			isCheck = true;
		}
	}
	else if(start.y-target.y == 0){
		auto sign = start.x < target.x ? 1 : -1;
		auto I = start.x+sign;
		//coordLine.push_back(start);
		while (I != target.x) {
			if (GetPieceAt(I, start.y).pieceType != none) {
				tempCheck = false;
			}
			//coordLine.push_back(Coord(I, start.y));
			I += sign;
		}
		if (tempCheck) {
			isCheck = true;
		}
	}
	return coordLine;
}

std::list<Coord> Board::GetDiagonalOfCoords(Coord start, Coord target) {
	std::list<Coord> coordLine;
	auto tempCheck = true;
	if (std::abs(start.x - target.x) == std::abs(start.y - target.y)) {
		auto signX = start.x < target.x ? 1 : -1;
		auto signY = start.y < target.y ? 1 : -1;
		auto I = start.x + signX;
		auto J = start.y + signY;
		//coordLine.push_back(start);
		while (I != target.x) {
			if (GetPieceAt(I, J).pieceType != none) {
				tempCheck = false;
			}
			//coordLine.push_back(Coord(I, J));
			I += signX;
			J += signY;
		}
		if(tempCheck) {
			isCheck = true;
		}
	}
	return coordLine;
}

std::list<Coord> Board::GetKnightChecks(Coord start, Coord target) {
	std::list<Coord> knightChecks;
	if (std::abs(start.x - target.x) == 1 && std::abs(start.y - target.y) == 2) {
		//knightChecks.push_back(start);
		isCheck = true;
	}
	if (std::abs(start.y - target.y) == 1 && std::abs(start.x - target.x) == 2) {
		//knightChecks.push_back(start);
		isCheck = true;
	}
	return knightChecks;

}

std::list<Coord> Board::GetPawnChecks(Coord start, Coord target, bool colorOfMover) {
	std::list<Coord> pawnChecks;
	if (!colorOfMover) {
		if (start.y-target.y==-1 && std::abs(start.x-target.x)==1) {
			//pawnChecks.push_back(start);
			isCheck = true;
		}
	}
	else {
		if (start.y - target.y == 1 && std::abs(start.x - target.x) == 1) {
			//pawnChecks.push_back(start);
			isCheck = true;
		}
	}
	return pawnChecks;
}

std::list<std::list<Coord>>& Board::GetCheckLines() {
	return checkLines;
}

bool Board::GetCheck() {
	return isCheck;
}

bool Board::IsCheck(bool color) {

}