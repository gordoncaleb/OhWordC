/*
 * Knight.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Knight.h"
namespace OhWordC {
Knight::Knight() {
	// TODO Auto-generated constructor stub

}
static PieceID Knight::getPieceID() {
	return KNIGHT;
}

static string Knight::getName() {
	return "Knight";
}

static string Knight::getStringID() {
	return "N";
}

static vector<long> Knight::generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int nextRow;
	int nextCol;
	int value;
	int bonus;
	int myValue = board->getPieceValue(p->getRow(), p->getCol());
	PositionStatus pieceStatus;
	side_t player = p->getSide();
	long moveLong;

	for (int i = 0; i < 8; i++) {
		nextRow = currentRow + KNIGHTMOVES[0][i];
		nextCol = currentCol + KNIGHTMOVES[1][i];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		if (pieceStatus != OFF_BOARD) {
			bonus = PositionBonus::getKnightMoveBonus(currentRow, currentCol, nextRow, nextCol, p->getSide());

			if (pieceStatus == NO_PIECE) {
				if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {

					if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
						value = -myValue >> 1;
					} else {
						value = bonus;
					}

					moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value);
					validMoves.push_back(moveLong);
				}
			}

			if (pieceStatus == ENEMY) {
				if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {
					value = board->getPieceValue(nextRow, nextCol);

					if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
						value -= myValue >> 1;
					} else {
						value += bonus;
					}

					moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value, NONE, board->getPiece(nextRow, nextCol));
					validMoves.push_back(moveLong);
				}
			}

		}
	}

	return validMoves;

}

static void Knight::getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo) {

	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int nextRow;
	int nextCol;
	PositionStatus pieceStatus;

	for (int i = 0; i < 8; i++) {
		nextRow = currentRow + KNIGHTMOVES[0][i];
		nextCol = currentCol + KNIGHTMOVES[1][i];

		pieceStatus = board->checkPiece(nextRow, nextCol, p->getSide());

		if (pieceStatus != OFF_BOARD) {

			if (board->getPieceID(nextRow, nextCol) == KING && pieceStatus == ENEMY) {
				nullMoveInfo[1] &= p->getBit();
			}

			nullMoveInfo[0] |= BitBoard::getMask(nextRow, nextCol);
		}
	}

}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}
}

