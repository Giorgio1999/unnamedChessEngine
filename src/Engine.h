#pragma once
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <string>
#include <list>

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

		std::list<Move> GetPseudoLegalMoves();	//Gets Pseudo legal moves
		void GetPseudoLegalPawnMoves(std::list<Move>& moveList, Piece current, int i, int j);	//function for every piecetype
		void GetPseudoLegalKnightMoves(std::list<Move>& moveList, Piece current, int i, int j);
		void GetPseudoLegalBishopMoves(std::list<Move>& moveList, Piece current, int i, int j);
		void GetPseudoLegalRookMoves(std::list<Move>& moveList, Piece current, int i, int j);
		void GetPseudoLegalQueenMoves(std::list<Move>& moveList, Piece current, int i, int j);
		void GetPseudoLegalKingMoves(std::list<Move>& moveList, Piece current, int i, int j);
		
		std::list<Move> GetLegalMoves();

		std::string GetBestMove();
		//void MakeMove(Move move);
		//void UndoMove(Move move);
		//bool InitialiseBoard(bool isStartpos, string fen="noFen");
};