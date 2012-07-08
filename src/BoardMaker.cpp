/*
 * BoardMaker.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#include "BoardMaker.h"

namespace OhWordC {

BoardMaker::BoardMaker() {
	// TODO Auto-generated constructor stub

}

static Board BoardMaker::getStandardChessBoard() {

	return makeBoard(1, 2, 2, 1, 2);
}

static Board BoardMaker::getRandomChess960Board() {

	return makeBoard(rollDie(4), rollDie(4), rollDie(6), rollDie(5), rollDie(4));
}

static Board BoardMaker::makeBoard(int r1, int r2, int r3, int r4, int r5) {
	vector<Piece>* pieces = new vector[2];
	pieces[0] = new vector<Piece>();
	pieces[1] = new vector<Piece>();

	int* pawnRow = new int[2];
	pawnRow[BLACK] = 1;
	pawnRow[WHITE] = 6;

	int* mainRow = new int[2];
	mainRow[BLACK] = 0;
	mainRow[WHITE] = 7;

	// public Piece(PieceID id, Side player, int row, int col, boolean
	// moved) {
	Piece temp;
	for (int s = 0; s < 2; s++) {
		for (int p = 0; p < 8; p++) {
			temp = new Piece(PAWN, (side_t) s, pawnRow[s], p, false);
			pieces[s].push_back(temp);
		}
	}

	PieceID* setup = new PieceID[8];

	setup[r1 * 2] = BISHOP;
	setup[r2 * 2 + 1] = BISHOP;

	setup[ithEmptyPosition(r3 + 1, setup)] = QUEEN;

	setup[ithEmptyPosition(r4 + 1, setup)] = KNIGHT;
	setup[ithEmptyPosition(r5 + 1, setup)] = KNIGHT;

	setup[ithEmptyPosition(2, setup)] = KING;

	setup[ithEmptyPosition(1, setup)] = ROOK;
	setup[ithEmptyPosition(1, setup)] = ROOK;

	for (int s = 0; s < 2; s++) {
		for (int p = 0; p < 8; p++) {
			temp = new Piece(setup[p], (side_t) s, mainRow[s], p, false);
			pieces[s].push_back(temp);
		}
	}

	Board board = new Board(pieces, (side_t) WHITE, *(new vector<Move>()), 0, 0);

	return board;
}

static int BoardMaker::ithEmptyPosition(int i, PieceID * setup) {
	for (int n = 0; n < 6; n++) {

		if (setup[n] == 0) {
			i--;
		}

		if (i <= 0) {
			return n;
		}
	}

	return 6;
}

static int BoardMaker::rollDie(int dieSize) {
	return (int) (Math.random() * (double) dieSize);
}

BoardMaker::~BoardMaker() {
	// TODO Auto-generated destructor stub
}

} /* namespace OhWordC */
