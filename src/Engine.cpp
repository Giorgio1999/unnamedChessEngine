#include "Engine.h"
#include "Board.h"
#include "Piece.h"
#include <string>

Engine::Engine(){
	this->board = Board();
}

void Engine::NewGame(){
	board.Clear();
}

void Engine::SetPosition(PieceList pieces) {
	board.SetPosition(pieces);
}

std::string Engine::ShowBoard() {
	return board.ShowBoard();
}