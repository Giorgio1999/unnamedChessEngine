#include "Engine.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include <list>

Engine::Engine(){
	this->board = Board();
}

void Engine::NewGame(){
	board.Clear();
}

void Engine::SetPosition(PieceList pieces) {
	board.SetPosition(pieces);
}

void Engine::MakeMove(Move move) {
	board.MakeMove(move);
}

void Engine::UndoLastMove() {
	board.UndoLastMove();
}

std::string Engine::ShowBoard() {
	return board.ShowBoard();
}

std::list<Move> Engine::GetLegalMoves() {
	std::list<Move> moveList;
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++) {
			Piece current = board.GetPieceAt(i,j);
			if (current.color == board.WhiteToMove()) {
				switch (current.pieceType) {
					case none:
						break;
					case pawn:
						GetLegalPawnMoves(moveList, current, i, j);
						break;
					case knight:
						GetLegalKnightMoves(moveList, current, i, j);
						break;
					case bishop:
						GetLegalBishopMoves(moveList, current, i, j);
						break;
					case rook:
						GetLegalRookMoves(moveList, current, i, j);
						break;
					case queen:
						GetLegalQueenMoves(moveList, current, i, j);
						break;
					case king:
						GetLegalKingMoves(moveList, current, i, j);
						break;
				}
			}
		}
	}
	return moveList;
}

void Engine::GetLegalPawnMoves(std::list<Move>& moveList, Piece current, int i, int j) {
	int sign = current.color ? -1 : 1;
	if (j + sign < 7 && j + sign > 0) {
		if(board.GetPieceAt(i,j+sign).pieceType==none){
			moveList.push_back(Move(i, j, i, j + sign));
			if (j + 2 * sign < 8 && j + 2 * sign >= 0) {
				if (board.GetPieceAt(i, j + 2*sign).pieceType == none && !current.hasMoved) {
					moveList.push_back(Move(i, j, i, j + 2*sign));
				}
			}
		}
	}
	for (int di = -1;di < 2;di += 2) {
		if (i + di < 8 && i + di >=0 && j + sign < 7 && j + sign > 0) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				moveList.push_back(Move(i, j, i + di, j + sign));
			}
		}
		if (i + di < 8 && i + di >= 0 && (j + sign == 7 || j + sign == 0)) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				Move promotion = Move(i, j, i + di, j + sign);
				promotion.convertTo = knight;
				moveList.push_back(promotion);
				promotion.convertTo = bishop;
				moveList.push_back(promotion);
				promotion.convertTo = rook;
				moveList.push_back(promotion);
				promotion.convertTo = queen;
				moveList.push_back(promotion);
			}
		}
	}
	if ((j + sign == 7 || j + sign == 0) && board.GetPieceAt(i,j+sign).pieceType==none) {
		Move promotion = Move(i, j, i, j + sign);
		promotion.convertTo = knight;
		moveList.push_back(promotion);
		promotion.convertTo = bishop;
		moveList.push_back(promotion);
		promotion.convertTo = rook;
		moveList.push_back(promotion);
		promotion.convertTo = queen;
		moveList.push_back(promotion);
	}
}

void Engine::GetLegalKnightMoves(std::list<Move>& moveList, Piece current, int i, int j){}

void Engine::GetLegalBishopMoves(std::list<Move>& moveList, Piece current, int i, int j){
	for (int n = 1;n < std::min(8-i,8-j);n++) {
		Piece other = board.GetPieceAt(i + n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i + n, j + n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(i, j);n++) {
		Piece other = board.GetPieceAt(i - n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i - n, j - n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(7 - i, j);n++) {
		Piece other = board.GetPieceAt(i + n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i + n, j - n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(i, 8 - j - 1);n++) {
		Piece other = board.GetPieceAt(i - n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i - n, j + n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetLegalRookMoves(std::list<Move>& moveList, Piece current, int i, int j){
	for (int n = i+1;n < 8;n++) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, n, j));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = i-1;n >=0;n--) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, n, j));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = j+1;n < i;n++) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i, n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = j-1;n >= 0;n--) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		moveList.push_back(Move(i, j, i, n));
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetLegalQueenMoves(std::list<Move>& moveList, Piece current, int i, int j){
	GetLegalRookMoves(moveList, current, i, j);
	GetLegalBishopMoves(moveList, current, i, j);
}

void Engine::GetLegalKingMoves(std::list<Move>& moveList, Piece current, int i, int j){}

