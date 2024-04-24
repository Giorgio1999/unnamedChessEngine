#pragma once
#include <string>
#include "Piece.h"

//This is all the functionality required to translate between "human readable" fen and engine language


const std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";	//hardcoded starting position

PieceList Fen2PieceList(std::string fen);	//FFen Parser