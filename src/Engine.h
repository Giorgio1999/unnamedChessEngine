#pragma once
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include <vector>

//This will include the core functionality

class Engine {
	private:
		Board board;	//internal board

	public:
		Engine();
		void NewGame();						//clears board for new game
		void SetPosition(PieceList pieces);	//Sets a given PieceList as position
		void MakeMove(Move move);			//Make a move
		void UndoLastMove();				//Reverts to previous position
		std::string ShowBoard();			//Debug tool to display current board in console

		void GetPseudoLegalMoves(std::vector<Move>& moveVector);	//Gets Pseudo legal moves and writes them into the given vector
		void GetPseudoLegalPawnMoves(std::vector<Move>& moveVector, Piece current, int i, int j);	//function for every piecetype
		void GetPseudoLegalKnightMoves(std::vector<Move>& moveVector, Piece current, int i, int j);
		void GetPseudoLegalBishopMoves(std::vector<Move>& moveVector, Piece current, int i, int j);
		void GetPseudoLegalRookMoves(std::vector<Move>& moveVector, Piece current, int i, int j);
		void GetPseudoLegalQueenMoves(std::vector<Move>& moveVector, Piece current, int i, int j);
		void GetPseudoLegalKingMoves(std::vector<Move>& moveVector, Piece current, int i, int j);
		
		void GetLegalMoves(std::vector<Move>& moveVector);

		std::string GetBestMove();

		int Perft(int depth);
		std::string SplitPerft(int depth);
		//void MakeMove(Move move);
		//void UndoMove(Move move);
		//bool InitialiseBoard(bool isStartpos, string fen="noFen");
};