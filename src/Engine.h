#pragma once
#include "Board.h"
#include "Piece.h"
#include <string>
//This will include the core functionality

class Engine {
	private:
		Board board;

	public:
		Engine();
		void NewGame();
		void SetPosition(PieceList pieces);
		std::string ShowBoard();

		//MoveList GetLegalMoves(bool captures);
		//void MakeMove(Move move);
		//void UndoMove(Move move);
		//bool InitialiseBoard(bool isStartpos, string fen="noFen");
};