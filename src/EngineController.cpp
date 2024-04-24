#include "EngineController.h"
#include "Engine.h"
#include "FenParser.h"
#include "Move.h"
#include <string>
#include <list>

EngineController::EngineController(){}

void EngineController::BootEngine() {
	this->engine = Engine::Engine();
}

void EngineController::NewGame() {
	engine.NewGame();
}

void EngineController::SetPosition() {
	engine.SetPosition(Fen2PieceList(startingPosition));
}

void EngineController::SetPosition(std::string fenString) {
	engine.SetPosition(Fen2PieceList(fenString));
}

void EngineController::MakeMoves(std::string moveHistory) {
	std::list<Move> moves = Str2Moves(moveHistory);
	while (moves.size() > 0) {
		engine.MakeMove(moves.front());
		moves.pop_front();
	}
}

bool EngineController::IsReady() {
	return this->isReady;
}

std::string EngineController::ShowBoard() {
	return engine.ShowBoard();
}