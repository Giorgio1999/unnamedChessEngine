#pragma once
#include "Engine.h"
#include <string>

//This will serve as an mediator between the uci handler and the engine
class EngineController {
	Engine engine;					//holds instance of engine
	bool isReady = true;			//no use as of yet
	public:
		EngineController();			
		void BootEngine();							//Boot engine
		void NewGame();								//Clears board for a new game
		void SetPosition();							//Sets starting position
		void SetPosition(std::string fenString);	//Sets position to fen string
		void MakeMoves(std::string moveHistory);	//Makes given moves on the board
		std::string GetLegalMoves();						//Gets legalmoves
		bool IsReady();								//returns ready flag
		std::string ShowBoard();					//Debug tool to display board in console
};