#include "EngineController.h"
#include "Engine.h"
#include "FenParser.h"
#include <string>

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

bool EngineController::IsReady() {
	return this->isReady;
}

std::string EngineController::ShowBoard() {
	return engine.ShowBoard();
}