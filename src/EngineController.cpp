#include "EngineController.h"
#include "Engine.h"
#include "FenParser.h"
#include "Move.h"
#include <string>
#include <list>
#include <chrono>

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
	std::vector<Move> moves = Str2Moves(moveHistory);
	for (const auto& move : moves){
		engine.MakeMove(move);
	}
}

bool EngineController::IsReady() {
	return this->isReady;
}

std::string EngineController::ShowBoard() {
	return engine.ShowBoard();
}

std::string EngineController::GetLegalMoves() {
	std::vector<Move> moveVector;
	engine.GetLegalMoves(moveVector);
	std::string legalMoveList = "";
	for (const auto& move : moveVector) {
		legalMoveList += Move2Str(move) + " ";
	}
	return legalMoveList;
}

std::string EngineController::Search() {
	return engine.GetBestMove();
}

std::string EngineController::Perft(int depth) {
	auto start = std::chrono::high_resolution_clock::now();
	int numberOfLeafs = engine.Perft(depth);
	auto end = std::chrono::high_resolution_clock::now();
	float duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto mnps = numberOfLeafs / duration / 1000000. * 60.;
	std::string returnString = "Positions found: " + std::to_string(numberOfLeafs) + ", Speed = " + std::to_string(mnps) + "Mn/s";
	return returnString;
}

std::string EngineController::SplitPerft(int depth) {
	return engine.SplitPerft(depth);
}