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
	return moveList;
}

void Engine::GetLegalPawnMoves(std::list<Move>& moveList, Piece current, int i, int j) {
	int sign = current.color ? -1 : 1;
	if (j + sign < 8 && j + sign >= 0) {
		if(board.GetPieceAt(i,j+sign).pieceType==none){
			moveList.push_back(Move(i, j, i, j + sign));
			if (j + 2 * sign < 8 && j + 2 * sign >= 0) {
				if (board.GetPieceAt(i, j + 2*sign).pieceType == none && !current.hasMoved) {
					moveList.push_back(Move(i, j, i, j + 2*sign));
				}
			}
		}
	}
	if (i + 1 < 8 && j + sign < 8 && j + sign >= 0) {
		if ((board.GetPieceAt(i + 1, j + sign).pieceType != none || board.GetPieceAt(i + 1, j + sign).isGhost) && board.GetPieceAt(i + 1, j + sign).color != current.color) {
			moveList.push_back(Move(i, j, i + 1, j + sign));
		}
	}
	if (i - 1 >= 0 && j + sign < 8 && j + sign >= 0) {
		if ((board.GetPieceAt(i - 1, j + sign).pieceType != none || board.GetPieceAt(i - 1, j + sign).isGhost) && board.GetPieceAt(i - 1, j + sign).color != current.color) {
			moveList.push_back(Move(i, j, i + 1, j + sign));
		}
	}
	if (j + sign == 7 || j + sign == 0) {
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
void Engine::GetLegalBishopMoves(std::list<Move>& moveList, Piece current, int i, int j){}
void Engine::GetLegalRookMoves(std::list<Move>& moveList, Piece current, int i, int j){}
void Engine::GetLegalQueenMoves(std::list<Move>& moveList, Piece current, int i, int j){}
void Engine::GetLegalKingMoves(std::list<Move>& moveList, Piece current, int i, int j){}

