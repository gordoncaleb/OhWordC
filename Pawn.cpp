/*
 * Pawn.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {
Pawn::Pawn() {
	// TODO Auto-generated constructor stub

}

static PieceID Pawn::getPieceID() {
	return PAWN;
}

static string Pawn::getName() {
	return "Pawn";
}

static string Pawn::getStringID() {
	return "P";
}

static vector<long> Pawn::generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int dir;
	int fifthRank;
	int value;
	int myValue = board->getPieceValue(p->getRow(), p->getCol());
	long moveLong;

//		System.out.println("pawn " + p.getCol() + " null move info");
//		System.out.println(BitBoard.printBitBoard(nullMoveInfo[0]));
//		System.out.println(BitBoard.printBitBoard(nullMoveInfo[1]));
//		System.out.println(BitBoard.printBitBoard(nullMoveInfo[2]));

	int* lr = { 1, -1 };

	if (player == WHITE) {
		dir = -1;
		fifthRank = 3;
	} else {
		dir = 1;
		fifthRank = 4;
	}

	if (board->checkPiece(currentRow + dir, currentCol, player) == NO_PIECE) {

		if (p->isValidMove(currentRow + dir, currentCol, nullMoveInfo)) {

			moveLong = Move::moveLong(currentRow, currentCol, currentRow + dir, currentCol, 0, NONE);

			value = PositionBonus::getPawnMoveBonus(currentRow, currentCol, currentRow + dir, currentCol, p->getSide());

			if ((currentRow + dir) == 0 || (currentRow + dir) == 7) {
				moveLong = Move::setNote(moveLong, MoveNote::NEW_QUEEN);
				value = Values::QUEEN_VALUE;
			}

			if ((nullMoveInfo[0] & BitBoard::getMask(currentRow + dir, currentCol)) != 0) {
				value = -myValue >> 1;
			}

			moveLong = Move::setValue(moveLong, value);

			validMoves.push_back(moveLong);

		}

		if (!p->hasMoved() && board->checkPiece(currentRow + 2 * dir, currentCol, player) == NO_PIECE) {

			if (p->isValidMove(currentRow + 2 * dir, currentCol, nullMoveInfo)) {

				value = PositionBonus::getPawnMoveBonus(currentRow, currentCol, currentRow + 2 * dir, currentCol, p->getSide());

				if ((nullMoveInfo[0] & BitBoard::getMask(currentRow + 2 * dir, currentCol)) != 0) {
					value = -myValue >> 1;
				}

				validMoves.push_back(Move::moveLong(currentRow, currentCol, currentRow + 2 * dir, currentCol, value, MoveNote::PAWN_LEAP));

			}
		}

	}

	// Check left and right attack angles
	for (int i = 0; i < 2; i++) {
		if (board->checkPiece(currentRow + dir, currentCol + lr[i], player) == ENEMY) {

			if (p->isValidMove(currentRow + dir, currentCol + lr[i], nullMoveInfo)) {

				moveLong = Move::moveLong(currentRow, currentCol, currentRow + dir, currentCol + lr[i]);

				value = PositionBonus::getPawnMoveBonus(currentRow, currentCol, currentRow + dir, currentCol, p->getSide());

				if ((currentRow + dir) == 0 || (currentRow + dir) == 7) {
					moveLong = Move::setNote(moveLong, MoveNote::NEW_QUEEN);
					value = Values::QUEEN_VALUE;
				}

				if ((nullMoveInfo[0] & BitBoard::getMask(currentRow + dir, currentCol + lr[i])) != 0) {
					value = board->getPieceValue(currentRow + dir, currentCol + lr[i]) - myValue >> 1;
				} else {
					value += board->getPieceValue(currentRow + dir, currentCol + lr[i]);
				}

				moveLong = Move::setValue(moveLong, value);

				moveLong = Move::setPieceTaken(moveLong, board->getPiece(currentRow + dir, currentCol + lr[i]));
				validMoves.push_back(moveLong);
			}

		}
	}

	// Check left and right en passant rule
	if (currentRow == fifthRank && board->getLastMoveMade() != 0) {
		for (int i = 0; i < 2; i++) {
			if (board->checkPiece(fifthRank, currentCol + lr[i], player) == ENEMY) {

				if ((Move::getToCol(board->getLastMoveMade()) == (currentCol + lr[i])) && Move::getNote(board->getLastMoveMade()) == PAWN_LEAP) {

					if (p->isValidMove(currentRow + dir, currentCol + lr[i], nullMoveInfo)) {

						value = board->getPieceValue(fifthRank, currentCol + lr[i]);

						if ((nullMoveInfo[0] & BitBoard::getMask(currentRow + dir, currentCol + lr[i])) != 0) {
							value -= myValue >> 1;
						}

						moveLong = Move::moveLong(currentRow, currentCol, currentRow + dir, currentCol + lr[i], value, ENPASSANT,
								board->getPiece(fifthRank, currentCol + lr[i]));
						validMoves.push_back(moveLong);
					}

				}
			}
		}
	}

	return validMoves;

}

static void Pawn::getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo) {

	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int dir;
	side_t player = p->getSide();
	PositionStatus pieceStatus;

	if (player == WHITE) {
		dir = -1;
	} else {
		dir = 1;
	}

	pieceStatus = board->checkPiece(currentRow + dir, currentCol - 1, player);

	if (pieceStatus != OFF_BOARD) {

		if (board->getPieceID(currentRow + dir, currentCol - 1) == KING && pieceStatus == ENEMY) {
			nullMoveInfo[1] &= p->getBit();
		}

		nullMoveInfo[0] |= BitBoard::getMask(currentRow + dir, currentCol - 1);
	}

	pieceStatus = board->checkPiece(currentRow + dir, currentCol + 1, player);

	if (pieceStatus != OFF_BOARD) {

		if (board->getPieceID(currentRow + dir, currentCol + 1) == KING && pieceStatus == ENEMY) {
			nullMoveInfo[1] &= p->getBit();
		}

		nullMoveInfo[0] |= BitBoard::getMask(currentRow + dir, currentCol + 1);
	}

}

Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}
}
