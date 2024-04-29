#include "Engine.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include <vector>

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

void Engine::GetPseudoLegalMoves(std::vector<Move>& moveVector) {
	for (auto i = 0;i < 8;i++) {
		for (auto j = 0;j < 8;j++) {
			Piece current = board.GetPieceAt(i,j);
			if (current.color == board.WhiteToMove()) {
				switch (current.pieceType) {
					case none:
						break;
					case pawn:
						GetPseudoLegalPawnMoves(moveVector, current, i, j);
						break;
					case knight:
						GetPseudoLegalKnightMoves(moveVector, current, i, j);
						break;
					case bishop:
						GetPseudoLegalBishopMoves(moveVector, current, i, j);
						break;
					case rook:
						GetPseudoLegalRookMoves(moveVector, current, i, j);
						break;
					case queen:
						GetPseudoLegalQueenMoves(moveVector, current, i, j);
						break;
					case king:
						GetPseudoLegalKingMoves(moveVector, current, i, j);
						break;
				}
			}
		}
	}
}

void Engine::GetPseudoLegalPawnMoves(std::vector<Move>& moveVector, Piece current, int i, int j) {
	Move move;
	auto sign = current.color ? -1 : 1;
	if (j + sign < 7 && j + sign > 0) {
		if(board.GetPieceAt(i,j+sign).pieceType==none){
			move = Move(i, j, i, j + sign);
			move.convertTo = pawn;
			moveVector.push_back(move);
			if (j + 2 * sign < 8 && j + 2 * sign >= 0) {
				if (board.GetPieceAt(i, j + 2*sign).pieceType == none && !current.hasMoved) {
					move = Move(i, j, i, j + 2 * sign);
					move.convertTo = pawn;
					moveVector.push_back(move);
				}
			}
		}
	}
	for (auto di = -1;di < 2;di += 2) {
		if (i + di < 8 && i + di >=0 && j + sign < 7 && j + sign > 0) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				move = Move(i, j, i + di, j + sign);
				move.convertTo = pawn;
				moveVector.push_back(move);
			}
		}
		if (i + di < 8 && i + di >= 0 && (j + sign == 7 || j + sign == 0)) {
			if ((board.GetPieceAt(i + di, j + sign).pieceType != none || board.GetPieceAt(i + di, j + sign).isGhost) && board.GetPieceAt(i + di, j + sign).color != current.color) {
				move = Move(i, j, i + di, j + sign);
				move.promotion = true;
				move.convertTo = knight;
				moveVector.push_back(move);
				move.convertTo = bishop;
				moveVector.push_back(move);
				move.convertTo = rook;
				moveVector.push_back(move);
				move.convertTo = queen;
				moveVector.push_back(move);
			}
		}
	}
	if ((j + sign == 7 || j + sign == 0) && board.GetPieceAt(i,j+sign).pieceType==none) {
		move = Move(i, j, i, j + sign);
		move.promotion = true;
		move.convertTo = knight;
		moveVector.push_back(move);
		move.convertTo = bishop;
		moveVector.push_back(move);
		move.convertTo = rook;
		moveVector.push_back(move);
		move.convertTo = queen;
		moveVector.push_back(move);
	}
}

void Engine::GetPseudoLegalKnightMoves(std::vector<Move>& moveVector, Piece current, int i, int j){
	Move move;
	for (auto dj = -2;dj < 3;dj += 4) {
		for (auto di = -1;di < 2;di += 2) {
			auto I = i + di;
			auto J = j + dj;
			if (I < 8 && I >= 0 && J < 8 && J >= 0) {
				Piece other = board.GetPieceAt(I, J);
				if (other.color != current.color || other.pieceType==none) {
					move = Move(i, j, I, J);
					move.convertTo = knight;
					moveVector.push_back(move);
				}
			}
			I = j + di;
			J = i + dj;
			if (I < 8 && I >= 0 && J < 8 && J >= 0) {
				Piece other = board.GetPieceAt(J, I);
				if (other.color != current.color || other.pieceType==none) {
					move = Move(i, j, J, I);
					move.convertTo = knight;
					moveVector.push_back(move);
				}
			}
		}
	}
}

void Engine::GetPseudoLegalBishopMoves(std::vector<Move>& moveVector, Piece current, int i, int j){
	Move move;
	for (auto n = 1;n < std::min(8-i,8-j);n++) {
		Piece other = board.GetPieceAt(i + n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i + n, j + n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = 1;n <= std::min(i, j);n++) {
		Piece other = board.GetPieceAt(i - n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i - n, j - n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = 1;n <= std::min(7 - i, j);n++) {
		Piece other = board.GetPieceAt(i + n, j - n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i + n, j - n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = 1;n <= std::min(i, 8 - j - 1);n++) {
		Piece other = board.GetPieceAt(i - n, j + n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i - n, j + n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetPseudoLegalRookMoves(std::vector<Move>& moveVector, Piece current, int i, int j){
	Move move;
	for (auto n = i+1;n < 8;n++) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, n, j);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = i-1;n >=0;n--) {
		Piece other = board.GetPieceAt(n, j);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, n, j);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = j+1;n < i;n++) {
		Piece other = board.GetPieceAt(i, n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i, n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
	for (auto n = j-1;n >= 0;n--) {
		Piece other = board.GetPieceAt(i, n);
		if (other.color == current.color && other.pieceType != none) {
			break;
		}
		move = Move(i, j, i, n);
		move.convertTo = current.pieceType;
		moveVector.push_back(move);
		if (other.color != current.color && other.pieceType != none) {
			break;
		}
	}
}

void Engine::GetPseudoLegalQueenMoves(std::vector<Move>& moveVector, Piece current, int i, int j){
	GetPseudoLegalRookMoves(moveVector, current, i, j);
	GetPseudoLegalBishopMoves(moveVector, current, i, j);
}

void Engine::GetPseudoLegalKingMoves(std::vector<Move>& moveVector, Piece current, int i, int j){
	Move move;
	for (auto di = -1;di < 2;di+=1) {
		for (auto dj = -1;dj < 2;dj+=1) {
			if (!(di == 0 && dj == 0)) {
				auto I = i + di;
				auto J = j + dj;
				if ((I < 8 && I >= 0 && J < 8 && J >= 0)) {
					Piece other = board.GetPieceAt(I, J);
					if (other.color != current.color || other.pieceType == none) {
						move = Move(i, j, I, J);
						move.convertTo = king;
						moveVector.push_back(move);
					}
				}
			}
		}
	}
	if (!current.hasMoved) {
		auto rights = board.GetCastleRights(current.color);
		auto noCastle = false;
		switch (rights)
		{
			case 1:
				for (auto I = i + 1;I < 7;I++) {
					if (board.GetPieceAt(I, j).pieceType != none) {
						noCastle = true;
						break;
					}
				}
				if (!noCastle) {
					move = Move(i, j, i + 2, j);
					move.convertTo = king;
					moveVector.push_back(move);
				}
				break;
			case 2:
				for (auto I = i - 1;I > 0;I--) {
					if (board.GetPieceAt(I, j).pieceType != none) {
						noCastle = true;
						break;
					}
				}
				if (!noCastle) {
					move = Move(i, j, i - 2, j);
					move.convertTo = king;
					moveVector.push_back(move);
				}
				break;
			case 3:
				for (auto I = i - 1;I > 0;I--) {
					if (board.GetPieceAt(I, j).pieceType != none) {
						noCastle = true;
						break;
					}
				}
				if (!noCastle) {
					move = Move(i, j, i - 2, j);
					move.convertTo = king;
					moveVector.push_back(move);
				}
				noCastle = false;
				for (auto I = i + 1;I < 6;I++) {
					if (board.GetPieceAt(I, j).pieceType != none) {
						noCastle = true;
						break;
					}
				}
				if (!noCastle) {
					move = Move(i, j, i + 2, j);
					move.convertTo = king;
					moveVector.push_back(move);
				}
				break;
		}
	}
}

std::string Engine::GetBestMove() {
	std::vector<Move> legalmoves;
	GetLegalMoves(legalmoves);
	return Move2Str(legalmoves[0]);
}

void Engine::GetLegalMoves(std::vector<Move>& moveVector) {
	std::vector<Move> pseudoMoves;
	GetPseudoLegalMoves(pseudoMoves);
	
	for (const auto& current : pseudoMoves) {
		bool color = board.WhiteToMove();
		bool tmpCheck;
		if (current == Move(4,7,6,7)) {	//e1g1
			board.MakeMove(Move(4,7,5,7));	//e1f1
			board.UpdateCheckLines(color);
			tmpCheck = board.GetCheck();
			board.UndoLastMove();
			board.MakeMove(Move(4, 7, 6, 7));	//e1g1
			tmpCheck |= board.GetCheck();
		}
		else if (current == Move(4,7,2,7)) {	//e1c1
			board.MakeMove(Move(4,7,3,7));	//e1d1
			board.UpdateCheckLines(color);
			tmpCheck = board.GetCheck();
			board.UndoLastMove();
			board.MakeMove(Move(4,7,2,7));	//e1c1
			board.UpdateCheckLines(color);
			tmpCheck |= board.GetCheck();
		}
		else if (current == Move(4,0,6,0)) {	//e8g8
			board.MakeMove(Move(4,0,5,0));	//e8f8
			board.UpdateCheckLines(color);
			tmpCheck = board.GetCheck();
			board.UndoLastMove();
			board.MakeMove(Move(4,0,6,0));	//e8g8
			tmpCheck |= board.GetCheck();
		}
		else if (current == Move(4,0,2,0)) {	//e8c8
			board.MakeMove(Move(4,0,3,0));	//e8d8
			board.UpdateCheckLines(color);
			tmpCheck = board.GetCheck();
			board.UndoLastMove();
			board.MakeMove(Move(4,0,2,0));	//e8c8
			board.UpdateCheckLines(color);
			tmpCheck |= board.GetCheck();
		}
		else {
			board.MakeMove(current);
			board.UpdateCheckLines(color);
			tmpCheck = board.GetCheck();
		}
		if (!tmpCheck) {
			moveVector.push_back(current);
		}
		board.UndoLastMove();
	}
}

int Engine::Perft(int depth) {
	std::vector<Move> legalMoves;
	GetLegalMoves(legalMoves);
	if (depth <= 0) {
		return (int)legalMoves.size();
	}
	int numberOfLeafs = 0;
	for (const auto& current : legalMoves) {
		board.MakeMove(current);
		numberOfLeafs += Perft(depth-1);
		board.UndoLastMove();
	}
	return numberOfLeafs;
}

std::string Engine::SplitPerft(int depth) {
	std::vector<Move> legalMoves;
	GetLegalMoves(legalMoves);
	std::string returnString = "";
	for (const auto& current : legalMoves) {
		board.MakeMove(current);
		returnString += Move2Str(current) + ": " + std::to_string(Perft(depth - 1)) + "\n";
		board.UndoLastMove();
	}
	return returnString;
}