/*
 * RNGTable.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {

int RNGTable::seed [8] =  {-52, 45, -101, 26, -51, -99, -84, -79};
RNGTable * RNGTable::singleton = NULL;

RNGTable::RNGTable() {
	rng = new SecureRandom(seed);
	generatePiecePerSquare();
	generateBlackToMove();
	generateCastlingRights();
	generateEnPassantFile();
}

RNGTable * RNGTable::getSingleton() {
	
	if(!singleton){
		singleton = new RNGTable();
	}

	return singleton;
}

__int64 RNGTable::randomLong() {
	return rng->nextLong();
}

void RNGTable::generatePiecePerSquare() {
	int numPieceType = 6;

	//piecePerSquare = new __int64[2][numPieceType][8][8];

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

__int64 RNGTable::getPiecePerSquareRandom(side_t player, PieceID id, int row, int col) {
	return piecePerSquare[player][id][row][col];
}

void RNGTable::generateBlackToMove() {
	blackToMove = randomLong();

}

__int64 RNGTable::getBlackToMoveRandom() {
	return blackToMove;
}

void RNGTable::generateCastlingRights() {
	//castlingRights = new __int64[2][2][2][2];

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

__int64 RNGTable::getCastlingRightsRandom(bool blackFarRook, bool blackNearRook, bool blackKing, bool whiteFarRook, bool whiteNearRook,
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
	//enPassantFile = new __int64[8];
	for (int f = 0; f < 8; f++) {
		enPassantFile[f] = randomLong();
	}
}

__int64 RNGTable::getEnPassantFile(int file) {
	return enPassantFile[file];
}

RNGTable::~RNGTable() {
	// TODO Auto-generated destructor stub
}
}
