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

std::list<Move> Engine::GetPseudoLegalMoves() {
	std::list<Move> moveList;
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++) {
			Piece current = board.GetPieceAt(i,j);
			if (current.color == board.WhiteToMove()) {
				switch (current.pieceType) {
					case none:
						break;
					case pawn:
						GetPseudoLegalPawnMoves(moveList, current, i, j);
						break;
					case knight:
						GetPseudoLegalKnightMoves(moveList, current, i, j);
						break;
					case bishop:
						GetPseudoLegalBishopMoves(moveList, current, i, j);
						break;
					case rook:
						GetPseudoLegalRookMoves(moveList, current, i, j);
						break;
					case queen:
						GetPseudoLegalQueenMoves(moveList, current, i, j);
						break;
					case king:
						GetPseudoLegalKingMoves(moveList, current, i, j);
						break;
				}
			}
		}
	}
	return moveList;
}

void Engine::GetPseudoLegalPawnMoves(std::list<Move>& moveList, Piece current, int i, int j) {
	Move move;
	int sign = current.color ? -1 : 1;
	if (j + sign < 7 && j + sign > 0) {
		if(board.GetPieceAt(i,j+sign).pieceType==none){
			move = Move(i, j, i, j + sign);
			move.convertTo = pawn;
			moveList.push_back(move);
			if (j + 2 * sign < 8 && j + 2 * sign >= 0) {
				if (board.GetPieceAt(i, j + 2*sign).pieceType == none && !current.hasMoved) {
					move = Move(i, j, i, j + 2 * sign);
					move.convertTo = pawn;
					moveList.push_back(move);
				}
			}
		}
	}
	for (int di = -1;di < 2;di += 2) {
		if (i + di < 8 && i + di >=0 && j + sign < 7 && j + sign > 0) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				move = Move(i, j, i + di, j + sign);
				move.convertTo = pawn;
				moveList.push_back(move);
			}
		}
		if (i + di < 8 && i + di >= 0 && (j + sign == 7 || j + sign == 0)) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				move = Move(i, j, i + di, j + sign);
				move.promotion = true;
				move.convertTo = knight;
				moveList.push_back(move);
				move.convertTo = bishop;
				moveList.push_back(move);
				move.convertTo = rook;
				moveList.push_back(move);
				move.convertTo = queen;
				moveList.push_back(move);
			}
		}
	}
	if ((j + sign == 7 || j + sign == 0) && board.GetPieceAt(i,j+sign).pieceType==none) {
		move = Move(i, j, i, j + sign);
		move.promotion = true;
		move.convertTo = knight;
		moveList.push_back(move);
		move.convertTo = bishop;
		moveList.push_back(move);
		move.convertTo = rook;
		moveList.push_back(move);
		move.convertTo = queen;
		moveList.push_back(move);
	}
}

void Engine::GetPseudoLegalKnightMoves(std::list<Move>& moveList, Piece current, int i, int j){
	Move move;
	for (int dj = -2;dj < 3;dj += 4) {
		for (int di = -1;di < 2;di += 2) {
			int I = i + di;
			int J = j + dj;
			if (I < 8 && I >= 0 && J < 8 && J >= 0) {
				Piece other = board.GetPieceAt(I, J);
				if (other.color != current.color || other.pieceType==none) {
					move = Move(i, j, I, J);
					move.convertTo = knight;
					moveList.push_back(move);
				}
			}
			I = j + di;
			J = i + dj;
			if (I < 8 && I >= 0 && J < 8 && J >= 0) {
				Piece other = board.GetPieceAt(J, I);
				if (other.color != current.color || other.pieceType==none) {
					move = Move(i, j, J, I);
					move.convertTo = knight;
					moveList.push_back(move);
				}
			}
		}
	}
}

void Engine::GetPseudoLegalBishopMoves(std::list<Move>& moveList, Piece current, int i, int j){
	Move move;
	for (int n = 1;n < std::min(8-i,8-j);n++) {
		Piece other = board.GetPieceAt(i + n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i + n, j + n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(i, j);n++) {
		Piece other = board.GetPieceAt(i - n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i - n, j - n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(7 - i, j);n++) {
		Piece other = board.GetPieceAt(i + n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i + n, j - n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = 1;n <= std::min(i, 8 - j - 1);n++) {
		Piece other = board.GetPieceAt(i - n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i - n, j + n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetPseudoLegalRookMoves(std::list<Move>& moveList, Piece current, int i, int j){
	Move move;
	for (int n = i+1;n < 8;n++) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, n, j);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = i-1;n >=0;n--) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, n, j);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = j+1;n < i;n++) {
		Piece other = board.GetPieceAt(i, n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i, n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (int n = j-1;n >= 0;n--) {
		Piece other = board.GetPieceAt(i, n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i, n);
		move.convertTo = current.pieceType;
		moveList.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetPseudoLegalQueenMoves(std::list<Move>& moveList, Piece current, int i, int j){
	GetPseudoLegalRookMoves(moveList, current, i, j);
	GetPseudoLegalBishopMoves(moveList, current, i, j);
}

void Engine::GetPseudoLegalKingMoves(std::list<Move>& moveList, Piece current, int i, int j){
	Move move;
	for (int di = -1;di < 2;di+=1) {
		for (int dj = -1;dj < 2;dj+=1) {
			if (!(di == 0 && dj == 0)) {
				int I = i + di;
				int J = j + dj;
				if ((I < 8 && I >= 0 && J < 8 && J >= 0)) {
					Piece other = board.GetPieceAt(I, J);
					if (other.color != current.color || other.pieceType == none) {
						move = Move(i, j, I, J);
						move.convertTo = king;
						moveList.push_back(move);
					}
				}
			}
		}
	}
	int rights = board.GetCastleRights(current.color);
	bool noCastle = false;
	switch (rights)
	{
		case 1:
			for (int I = i + 1;I < 7;I++) {
				if (board.GetPieceAt(I, j).pieceType != none) {
					noCastle = true;
					break;
				}
			}
			if (!noCastle) {
				move = Move(i, j, i + 2, j);
				move.convertTo = king;
				moveList.push_back(move);
			}
			break;
		case 2:
			for (int I = i - 1;I > 0;I--) {
				if (board.GetPieceAt(I, j).pieceType != none) {
					noCastle = true;
					break;
				}
			}
			if (!noCastle) {
				move = Move(i, j, i - 2, j);
				move.convertTo = king;
				moveList.push_back(move);
			}
			break;
		case 3:
			for (int I = i - 1;I > 0;I--) {
				if (board.GetPieceAt(I, j).pieceType != none) {
					noCastle = true;
					break;
				}
			}
			if (!noCastle) {
				move = Move(i, j, i - 2, j);
				move.convertTo = king;
				moveList.push_back(move);
			}
			noCastle = false;
			for (int I = i + 1;I < 6;I++) {
				if (board.GetPieceAt(I, j).pieceType != none) {
					noCastle = true;
					break;
				}
			}
			if (!noCastle) {
				move = Move(i, j, i + 2, j);
				move.convertTo = king;
				moveList.push_back(move);
			}
			break;
	}
}

std::string Engine::GetBestMove() {
	return Move2Str(GetPseudoLegalMoves().front());
}

std::list<Move> Engine::GetLegalMoves() {
	std::list<Move> pseudoMoves = GetPseudoLegalMoves();
	std::list<std::list<Coord>> checkLines = board.GetCheckLines();
	std::list<Move> legalMoves;
	if (board.GetCheck()) {
		for (int i = 0;i < pseudoMoves.size();i++) {
			Move current = pseudoMoves.back();	pseudoMoves.pop_back();
			Coord target = current.targetCoord;
			bool contains = current.convertTo == king;

			for (int j = 0;j < checkLines.size();j++) {
				std::list<Coord> checkLine = checkLines.back(); checkLines.pop_back();

				for (int k = 0;k < checkLine.size();k++) {
					Coord checkCoord = checkLine.back();	checkLine.pop_back();
					if (checkCoord == target && current.convertTo != king) {
						contains = true;
					}
					else if (checkCoord == target && current.convertTo == king) {
						contains = false;
					}
					checkLine.push_front(checkCoord);
				}

				checkLines.push_front(checkLine);
			}
			if (contains) {
				legalMoves.push_front(current);
			}
			pseudoMoves.push_front(current);
		}
	}
	while (pseudoMoves.size() > 0) {
		Move current = pseudoMoves.back();	pseudoMoves.pop_back();
		Coord start = current.startCoord;
		Coord target = current.targetCoord;
		bool containsStart = current.convertTo == king;	//this is because for the kin everything is reversed
		bool containsTarget = current.convertTo == king;
		if (current.convertTo != king) {
			for (int j = 0;j < checkLines.size();j++) {
				std::list<Coord> checkLine = checkLines.back(); checkLines.pop_back();

				for (int k = 0;k < checkLine.size();k++) {
					Coord checkCoord = checkLine.back();	checkLine.pop_back();
					if (checkCoord == target) {
						containsTarget = true;
					}
					if (checkCoord == start) {
						containsStart = true;
					}
					checkLine.push_front(checkCoord);
				}

				checkLines.push_front(checkLine);
			}
			if (containsStart) {
				if (containsTarget) {
					legalMoves.push_front(current);
				}
			}
			else {
				legalMoves.push_front(current);
			}
		}
		//Seperate Treatment of King (of course). The king is not allowed to step into check. Therefore if its not currently check, we have to make
		//every king move on the board and check wheter it is now check
		else {
			bool kingColor = board.WhiteToMove();
			board.MakeMove(current);	//There might be a chance to implement a quicker version of make move only for king moves
			board.UpdateCheckLines(kingColor);	//Update Check lines but with respect to the old king
			bool isCheckAfterMove = board.GetCheck();	//Test wheter the player who made the king move is now in check
			board.UndoLastMove();	//Revert board back to original state
			if (!isCheckAfterMove) {
				legalMoves.push_back(current);
			}
		}
	}
	return legalMoves;
}