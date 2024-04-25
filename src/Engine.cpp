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

