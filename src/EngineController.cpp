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

std::string EngineController::GetLegalMoves() {
	std::list<Move> moveList =  engine.GetLegalMoves();
	std::string legalMoveList = "";
	while(moveList.size()>0) {
		legalMoveList += Move2Str(moveList.back()) + " ";
		moveList.pop_back();
	}
	return legalMoveList;
}

std::string EngineController::Search() {
	return engine.GetBestMove();
}

std::string EngineController::Perft(int depth) {
	int numberOfLeafs = engine.Perft(depth);
	std::string returnString = "" + std::to_string(numberOfLeafs);
	return returnString;
}

std::string EngineController::SplitPerft(int depth) {
	return engine.SplitPerft(depth);
}