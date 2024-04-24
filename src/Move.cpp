#include "Move.h"
#include <string>
#include <list>

Coord::Coord(){
	x = 0;
	y = 0;
}
Coord::Coord(int _x, int _y) {
	x = _x;
	y = _y;
}

Move::Move() {
	startCoord = Coord();
	targetCoord = Coord();
}

Move::Move(Coord _startCoord, Coord _targetCoord) {
	startCoord = _startCoord;
	targetCoord = _targetCoord;
}

std::string Coord2Str(Coord coord) {
	return std::to_string(cols[coord.x]) + std::to_string(rows[coord.y]);
}

Coord Str2Coord(std::string coordString) {
	return Coord(cols.find(coordString[0]), rows.find(coordString[1]));
}

std::string Move2Str(Move move) {
	return Coord2Str(move.startCoord) + Coord2Str(move.targetCoord);
}

Move Str2Move(std::string moveString) {
	return Move(Str2Coord(moveString.substr(0, 2)), Str2Coord(moveString.substr(2, 4)));
}

std::list<Move> Str2Moves(std::string movesString) {
	std::list<Move> moves;
	std::string currentMove = "";
	while (movesString.length() > 0) {
		std::string currentMove = movesString.substr(0, movesString.find(' '));
		moves.push_back(Str2Move(currentMove));
		movesString = movesString.substr(currentMove.length(), movesString.length());
	}
	return moves;
}

int Coord2Index(Coord coord) {
	return coord.y * 8 + coord.x;
}

bool operator!=(Move lhs, Move rhs) {
	return lhs.startCoord == rhs.startCoord && lhs.targetCoord == rhs.targetCoord;
}

bool operator==(Coord lhs, Coord rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}