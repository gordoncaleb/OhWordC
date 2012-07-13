/*
 * Knight.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {

int Knight::KNIGHTMOVES [2][8] = { { 2, 2, -2, -2, 1, -1, 1, -1 }, { 1, -1, 1, -1, 2, 2, -2, -2 } };

Knight::Knight() {
	// TODO Auto-generated constructor stub

}
PieceID Knight::getPieceID() {
	return KNIGHT;
}

string Knight::getName() {
	return "Knight";
}

string Knight::getStringID() {
	return "N";
}

vector<__int64> Knight::generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> validMoves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int nextRow;
	int nextCol;
	int value;
	int bonus;
	int myValue = board->getPieceValue(p->getRow(), p->getCol());
	PositionStatus pieceStatus;
	side_t player = p->getSide();
	__int64 moveLong;

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

void Knight::getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo) {

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

