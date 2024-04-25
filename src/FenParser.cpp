#include "FenParser.h"
#include "Piece.h"
#include "Move.h"
#include <string>

PieceList Fen2PieceList(std::string fen) {
	PieceList pieces = PieceList();
	std::string position = fen.substr(0, fen.find_first_of(' '));
	int increment = 0;
	for (int i = 0; i < position.length();i++) {
		char current = position[i];
		if (current != '/') {
			switch (current) {
				case 'r':
					pieces.pieces[increment] = Piece(false, rook);
					increment++;
					break;
				case 'n':
					pieces.pieces[increment] = Piece(false, knight);
					increment++;
					break;
				case 'b':
					pieces.pieces[increment] = Piece(false, bishop);
					increment++;
					break;
				case 'q':
					pieces.pieces[increment] = Piece(false, queen);
					increment++;
					break;
				case 'k':
					pieces.pieces[increment] = Piece(false, king);
					increment++;
					break;
				case 'p':
					pieces.pieces[increment] = Piece(false, pawn);
					increment++;
					break;
				case 'R':
					pieces.pieces[increment] = Piece(true, rook);
					increment++;
					break;
				case 'N':
					pieces.pieces[increment] = Piece(true, knight);
					increment++;
					break;
				case 'B':
					pieces.pieces[increment] = Piece(true, bishop);
					increment++;
					break;
				case 'Q':
					pieces.pieces[increment] = Piece(true, queen);
					increment++;
					break;
				case 'K':
					pieces.pieces[increment] = Piece(true, king);
					increment++;
					break;
				case 'P':
					pieces.pieces[increment] = Piece(true, pawn);
					increment++;
					break;
				case '1':
					pieces.pieces[increment] = Piece();
					increment++;
					break;
				case '2':
					for (auto j = 0;j < 2;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 2;
					break;
				case '3':
					for (auto j = 0;j < 3;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 3;
					break;
				case '4':
					for (auto j = 0;j < 4;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 4;
					break;
				case '5':
					for (auto j = 0;j < 5;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 5;
					break;
				case '6':
					for (auto j = 0;j < 6;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 6;
					break;
				case '7':
					for (auto j = 0;j < 7;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 7;
					break;
				case '8':
					for (auto j = 0;j < 8;j++) {
						pieces.pieces[increment + j] = Piece();
					}
					increment += 8;
					break;
			}
		}
	}
	std::string rights = fen.substr(fen.find_first_of(' ') + 1, fen.length() - 1);
	char current = rights[0];
	switch (current) {
		case 'w':
			pieces.whiteToMove = true;
			break;
		case 'b':
			pieces.whiteToMove = false;
			break;
	}

	std::string castling = rights.substr(2, rights.length()-1);
	castling = castling.substr(0, castling.find_first_of(' '));
	for (int i = 0; i < castling.length(); i++) {
		switch (castling[i]) {
			case 'K':
				pieces.whiteKingsideCastleRight = true;
				break;
			case 'Q':
				pieces.whiteQueensideCastleRight = true;
				break;
			case 'k':
				pieces.blackKingsideCastleRight = true;
				break;
			case 'q':
				pieces.blackQueensideCastleRight = true;
			case '-':
				break;
		}
	}
	std::string enPassant = rights.substr(castling.length()+3, rights.length() - 1);
	enPassant = enPassant.substr(0, enPassant.find_first_of(' '));
	if (enPassant == "-") {
		pieces.isEnpassantable = false;
	}
	else {
		Piece ghost = Piece(!pieces.whiteToMove, none);
		ghost.isGhost = true;
		pieces.pieces[Coord2Index(Str2Coord(enPassant))] = ghost;
	}
	return pieces;
}