#pragma once
#include <string>
#include <list>

//Logic for handling moves


const std::string rows = "12345678";	//Hardcoded translations of the rows or y
const std::string cols = "abcdefgh";	//Hardcoded translations of the cols or x

struct Coord 
{
	int x = 0;
	int y = 0;

	Coord();
	Coord(int _x, int _y);
};


struct Move
{
	Coord startCoord;		//from
	Coord targetCoord;		//to

	Move();
	Move(Coord _startCoord, Coord _targetCoord);
};	

const Move nullMove = Move();


std::string Coord2Str(Coord coord);			//Helper functions to convert from human readable strings to moves and coords
Coord Str2Coord(std::string coordString);
std::string Move2Str(Move move);
Move Str2Move(std::string moveString);
std::list<Move> Str2Moves(std::string movesString);
int Coord2Index(Coord coord);				//convert between coord and 1d Board index
bool operator!=(Move lhs, Move rhs);		//To compare moves
bool operator==(Coord lhs, Coord rhs);		//To compare coords