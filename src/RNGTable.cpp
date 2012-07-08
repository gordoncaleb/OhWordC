/*
 * RNGTable.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "RNGTable.h"
namespace OhWordC {
RNGTable::RNGTable() {
	rng = new SecureRandom(seed);
	generatePiecePerSquare();
	generateBlackToMove();
	generateCastlingRights();
	generateEnPassantFile();
}

static RNGTable RNGTable::getSingleton() {
	if (singleton == 0) {
		singleton = new RNGTable();
	}
	return singleton;
}

long RNGTable::randomLong() {
	return rng.nextLong();
}

void RNGTable::generatePiecePerSquare() {
	int numPieceType = 6;

	piecePerSquare = new long[2][numPieceType][8][8];

	for (int player = 0; player < 2; player++) {
		for (int pieceType = 0; pieceType < numPieceType; pieceType++) {
			for (int r = 0; r < 8; r++) {
				for (int c = 0; c < 8; c++) {
					piecePerSquare[player][pieceType][r][c] = randomLong();
				}
			}
		}
	}
}

long RNGTable::getPiecePerSquareRandom(side_t player, PieceID id, int row, int col) {
	return piecePerSquare[player][id][row][col];
}

void RNGTable::generateBlackToMove() {
	blackToMove = randomLong();

}

long RNGTable::getBlackToMoveRandom() {
	return blackToMove;
}

void RNGTable::generateCastlingRights() {
	castlingRights = new long[2][2][2][2];

	for (int br = 0; br < 2; br++) {
		for (int bl = 0; bl < 2; bl++) {
			for (int wr = 0; wr < 2; wr++) {
				for (int wl = 0; wl < 2; wl++) {
					castlingRights[br][bl][wr][wl] = randomLong();
				}
			}
		}
	}
}

long RNGTable::getCastlingRightsRandom(bool blackFarRook, bool blackNearRook, bool blackKing, bool whiteFarRook, bool whiteNearRook,
		bool whiteKing) {

	int blackLeft = 0;
	int blackRight = 0;
	int whiteLeft = 0;
	int whiteRight = 0;

	if (!blackKing) {
		if (!blackFarRook) {
			blackLeft = 1;
		}
		if (!blackNearRook) {
			blackRight = 1;
		}
	}

	if (!whiteKing) {
		if (!whiteFarRook) {
			whiteLeft = 1;
		}
		if (!whiteNearRook) {
			whiteRight = 1;
		}
	}

	return castlingRights[blackLeft][blackRight][whiteRight][whiteLeft];
}

void RNGTable::generateEnPassantFile() {
	enPassantFile = new long[8];
	for (int f = 0; f < 8; f++) {
		enPassantFile[f] = randomLong();
	}
}

long RNGTable::getEnPassantFile(int file) {
	return enPassantFile[file];
}

RNGTable::~RNGTable() {
	// TODO Auto-generated destructor stub
}
}
