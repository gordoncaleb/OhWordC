/*
 * Rook.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {
Rook::Rook() {
	// TODO Auto-generated constructor stub

}

static PieceID Rook::getPieceID() {
	return ROOK;
}

static string Rook::getName() {
	return "Rook";
}

static string Rook::getStringID() {
	return "R";
}

static void Rook::generateMoves(Piece* p, Board* board, vector<long> moves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int nextRow;
	int nextCol;
	int value;
	PositionStatus pieceStatus;
	long moveLong;

	int i = 1;
	for (int d = 0; d < 4; d++) {
		nextRow = currentRow + i * ROOKMOVES[0][d];
		nextCol = currentCol + i * ROOKMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		while (pieceStatus == NO_PIECE) {

			if (!p->hasMoved() && !board->kingHasMoved(player)) {
				value = Values::CASTLE_ABILITY_LOST_VALUE;
			} else {
				value = 0;
			}

			moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value);

			moves.push_back(moveLong);

			i++;
			nextRow = currentRow + i * ROOKMOVES[0][d];
			nextCol = currentCol + i * ROOKMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);

		}

		if (pieceStatus == ENEMY) {

			if (!p->hasMoved() && !board->kingHasMoved(player)) {
				value = board->getPieceValue(nextRow, nextCol) + Values::CASTLE_ABILITY_LOST_VALUE;
			} else {
				value = board->getPieceValue(nextRow, nextCol);
			}

			moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value, NONE, board->getPiece(nextRow, nextCol));

			moves.push_back(moveLong);

		}

		i = 1;
	}

}

static vector<long> Rook::generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {

	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int nextRow;
	int nextCol;
	int value;
	PositionStatus pieceStatus;
	long moveLong;

	int i = 1;
	for (int d = 0; d < 4; d++) {
		nextRow = currentRow + i * ROOKMOVES[0][d];
		nextCol = currentCol + i * ROOKMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		while (pieceStatus == NO_PIECE) {

			if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {

				if (!p->hasMoved() && !board->kingHasMoved(player)) {
					value = Values::CASTLE_ABILITY_LOST_VALUE;
				} else {
					value = 0;
				}

				if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
					value -= Values::ROOK_VALUE >> 1;
				}

				moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value);

				validMoves.push_back(moveLong);
			}

			i++;
			nextRow = currentRow + i * ROOKMOVES[0][d];
			nextCol = currentCol + i * ROOKMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);

		}

		if (pieceStatus == ENEMY) {
			if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {

				if (!p->hasMoved() && !board->kingHasMoved(player)) {
					value = board->getPieceValue(nextRow, nextCol) + Values::CASTLE_ABILITY_LOST_VALUE;
				} else {
					value = board->getPieceValue(nextRow, nextCol);
				}

				if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
					value -= Values::ROOK_VALUE >> 1;
				}

				moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value, NONE, board->getPiece(nextRow, nextCol));

				validMoves.push_back(moveLong);
			}
		}

		i = 1;
	}

	return validMoves;

}

static void Rook::getNullMoveInfo(Piece* piece, Board* board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors,
		long friendly) {

	long bitPiece = piece->getBit();

	// up ------------------------------------------------------------
	unsigned long temp = bitPiece;
	unsigned long temp2 = bitPiece;
	int r = piece->getRow();
	int c = piece->getCol();
	long attackVector = 0;

	while ((temp2 = (temp2 >> 8 & updown)) != 0) {
		attackVector |= temp2;
		temp = temp2;
		r--;
	}

	temp = temp >> 8;
	nullMoveInfo[0] |= attackVector | temp;

	// check to see if king collision is possible
	if ((BitBoard::getColMask(c) & kingBitBoard) != 0) {

		if ((temp & kingBitBoard) != 0) {
			nullMoveInfo[1] &= attackVector | bitPiece;
			nullMoveInfo[2] |= temp >> 8;
		} else {
			if ((temp & friendly) != 0) {
				temp = temp >> 8;
				if ((temp & kingCheckVectors) != 0) {
					board->getPiece(r - 1, c).setBlockingVector(BitBoard::getColMask(c));
				}
			}
		}
	}

// down-----------------------------------------------------------
	temp = bitPiece;
	temp2 = bitPiece;
	r = piece->getRow();
	attackVector = 0;

	while ((temp2 = (temp2 << 8 & updown)) != 0) {
		attackVector |= temp2;
		temp = temp2;
		r++;
	}

	temp = temp << 8;
	nullMoveInfo[0] |= attackVector | temp;

// check to see if king collision is possible
	if ((BitBoard::getColMask(c) & kingBitBoard) != 0) {

		if ((temp & kingBitBoard) != 0) {
			nullMoveInfo[1] &= attackVector | bitPiece;
			nullMoveInfo[2] |= temp << 8;
		} else {
			if ((temp & friendly) != 0) {
				temp = temp << 8;
				if ((temp & kingCheckVectors) != 0) {
					board->getPiece(r + 1, c).setBlockingVector(BitBoard::getColMask(c));
				}
			}
		}
	}

// going westward -----------------------------------------------------
	if ((bitPiece & 0x0101010101010101L) == 0) {

		// west
		temp = bitPiece;
		temp2 = bitPiece;
		r = piece->getRow();
		attackVector = 0;

		while ((temp2 = (temp2 >> 1 & left)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			c--;
		}

		temp = temp >> 1;
		nullMoveInfo[0] |= attackVector | temp;

		// check to see if king collision is possible
		if ((BitBoard::getRowMask(r) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp >> 1;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp >> 1;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r, c - 1).setBlockingVector(BitBoard::getRowMask(r));
					}
				}
			}
		}

	}

	// going eastward
	if ((bitPiece & 0x8080808080808080L) == 0) {

// east
		temp = bitPiece;
		temp2 = bitPiece;
		r = piece->getRow();
		c = piece->getCol();
		attackVector = 0;

		while ((temp2 = (temp2 << 1 & right)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			c++;
		}

		temp = temp << 1;
		nullMoveInfo[0] |= attackVector | temp;

// check to see if king collision is possible
		if ((BitBoard::getRowMask(r) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp << 1;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp << 1;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r, c + 1).setBlockingVector(BitBoard::getRowMask(r));
					}
				}
			}
		}

	}

}

static void Rook::getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo) {
	long bitAttackVector = 0;
	long bitAttackCompliment = 0;
	bool inCheck = false;
	Piece blockingPiece;

	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int nextRow;
	int nextCol;
	PositionStatus pieceStatus;
	side_t player = p->getSide();

	long bitPosition = p->getBit();

	int i = 1;
	for (int d = 0; d < 4; d++) {
		nextRow = currentRow + i * ROOKMOVES[0][d];
		nextCol = currentCol + i * ROOKMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		if (pieceStatus == OFF_BOARD) {
			continue;
		}

		while (pieceStatus == NO_PIECE) {
			bitAttackVector |= BitBoard::getMask(nextRow, nextCol);
			i++;
			nextRow = currentRow + i * ROOKMOVES[0][d];
			nextCol = currentCol + i * ROOKMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);
		}

		if (pieceStatus != OFF_BOARD) {
			bitAttackVector |= BitBoard::getMask(nextRow, nextCol);
		}

		if (pieceStatus == ENEMY) {
			blockingPiece = board->getPiece(nextRow, nextCol);

			if (blockingPiece.getPieceID() == KING) {
				nullMoveInfo[1] &= (bitAttackVector | bitPosition);
				inCheck = true;
			}

			i++;
			nextRow = currentRow + i * ROOKMOVES[0][d];
			nextCol = currentCol + i * ROOKMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);

			while (pieceStatus == NO_PIECE) {
				bitAttackCompliment |= BitBoard::getMask(nextRow, nextCol);
				i++;
				nextRow = currentRow + i * ROOKMOVES[0][d];
				nextCol = currentCol + i * ROOKMOVES[1][d];
				pieceStatus = board->checkPiece(nextRow, nextCol, player);
			}

			if (pieceStatus != OFF_BOARD) {
				if (board->getPieceID(nextRow, nextCol) == KING && board->getPiece(nextRow, nextCol).getSide() != player) {
					blockingPiece.setBlockingVector(bitAttackCompliment | bitAttackVector | bitPosition);
				}
			}

			if (pieceStatus == FRIEND) {
				bitAttackCompliment |= BitBoard::getMask(nextRow, nextCol);
			}

		}

		nullMoveInfo[0] |= bitAttackVector;

		if (inCheck) {
			nullMoveInfo[2] |= bitAttackCompliment;
			inCheck = false;
		}

		bitAttackCompliment = 0;
		bitAttackVector = 0;

		i = 1;
	}

}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}
}
