#pragma once
#include "Engine.h"
#include <string>

//This will serve as an mediator between the uci handler and the engine
class EngineController {
	Engine engine;
	bool isReady = true;
	public:
		EngineController();
		void BootEngine();
		void NewGame();
		void SetPosition();
		void Go();
		bool IsReady();
		std::string ShowBoard();
};