/*
 * Queen.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Queen.h"
namespace OhWordC {
Queen::Queen() {
	// TODO Auto-generated constructor stub

}

static PieceID Queen::getPieceID() {
	return QUEEN;
}

static string Queen::getName() {
	return "Queen";
}

static string Queen::getStringID() {
	return "Q";
}

static void Queen::generateMoves(Piece* p, Board* board, vector<long> moves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	int nextRow;
	int nextCol;
	PositionStatus pieceStatus;

	int i = 1;
	for (int d = 0; d < 8; d++) {
		nextRow = currentRow + i * QUEENMOVES[0][d];
		nextCol = currentCol + i * QUEENMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, p->getSide());

		while (pieceStatus == NO_PIECE) {

			moves.push_back(Move::moveLong(currentRow, currentCol, nextRow, nextCol, 0, NONE));

			i++;
			nextRow = currentRow + i * QUEENMOVES[0][d];
			nextCol = currentCol + i * QUEENMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, p->getSide());

		}

		if (pieceStatus == ENEMY) {
			moves.push_back(
					Move::moveLong(currentRow, currentCol, nextRow, nextCol, board->getPieceValue(nextRow, nextCol), NONE, board->getPiece(nextRow, nextCol)));
		}

		i = 1;
	}
}

static vector<long> Queen::generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int nextRow;
	int nextCol;
	int value;
	PositionStatus pieceStatus;

	int i = 1;
	for (int d = 0; d < 8; d++) {
		nextRow = currentRow + i * QUEENMOVES[0][d];
		nextCol = currentCol + i * QUEENMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		while (pieceStatus == NO_PIECE) {

			if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {

				if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
					value = -Values::QUEEN_VALUE >> 1;
				} else {
					value = 0;
				}

				validMoves.push_back(Move::moveLong(currentRow, currentCol, nextRow, nextCol, value, NONE));
			}

			i++;
			nextRow = currentRow + i * QUEENMOVES[0][d];
			nextCol = currentCol + i * QUEENMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);

		}

		if (pieceStatus == ENEMY) {
			if (p->isValidMove(nextRow, nextCol, nullMoveInfo)) {

				value = board->getPieceValue(nextRow, nextCol);

				if ((nullMoveInfo[0] & BitBoard::getMask(nextRow, nextCol)) != 0) {
					value -= Values::QUEEN_VALUE >> 1;
				}

				long moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, value, NONE, board->getPiece(nextRow, nextCol));
				validMoves.push_back(moveLong);
			}
		}

		i = 1;
	}

	return validMoves;

}

static void getNullMoveInfo(Piece* piece, Board* board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors,
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

		// northwest
		temp2 = bitPiece;
		temp = bitPiece;
		c = piece->getCol();
		attackVector = 0;

		while ((temp2 = (temp2 >> 9 & left)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			r--;
			c--;
		}
		temp = temp >> 9;
		nullMoveInfo[0] |= attackVector | temp;

		// check to see if king collision is possible
		if ((BitBoard::getNegSlope(r, c) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp >> 9;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp >> 9;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r - 1, c - 1).setBlockingVector(BitBoard::getNegSlope(r, c));
					}
				}
			}
		}

		// south west
		temp = bitPiece;
		temp2 = bitPiece;
		r = piece->getRow();
		c = piece->getCol();
		attackVector = 0;

		while ((temp2 = (temp2 << 7 & left)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			r++;
			c--;
		}

		temp = temp << 7;
		nullMoveInfo[0] |= attackVector | temp;

		// check to see if king collision is possible
		if ((BitBoard::getPosSlope(r, c) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp << 7;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp << 7;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r + 1, c - 1).setBlockingVector(BitBoard::getPosSlope(r, c));
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

		// northeast
		temp = bitPiece;
		temp2 = bitPiece;
		c = piece->getCol();
		attackVector = 0;

		while ((temp2 = (temp2 >> 7 & right)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			c++;
			r--;
		}

		temp = temp >> 7;
		nullMoveInfo[0] |= attackVector | temp;

		// check to see if king collision is possible
		if ((BitBoard::getPosSlope(r, c) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp >> 7;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp >> 7;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r - 1, c + 1).setBlockingVector(BitBoard::getPosSlope(r, c));
					}
				}
			}
		}

		// southeast
		temp = bitPiece;
		temp2 = bitPiece;
		c = piece->getCol();
		r = piece->getRow();
		attackVector = 0;

		while ((temp2 = (temp2 << 9 & right)) != 0) {
			attackVector |= temp2;
			temp = temp2;
			c++;
			r++;
		}

		temp = temp << 9;
		nullMoveInfo[0] |= attackVector | temp;

		// check to see if king collision is possible
		if ((BitBoard::getNegSlope(r, c) & kingBitBoard) != 0) {

			if ((temp & kingBitBoard) != 0) {
				nullMoveInfo[1] &= attackVector | bitPiece;
				nullMoveInfo[2] |= temp << 9;
			} else {
				if ((temp & friendly) != 0) {
					temp = temp << 9;
					if ((temp & kingCheckVectors) != 0) {
						board->getPiece(r + 1, c + 1).setBlockingVector(BitBoard::getNegSlope(r, c));
					}
				}
			}
		}

	}

}

static void Queen::getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo) {
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
	for (int d = 0; d < 8; d++) {
		nextRow = currentRow + i * QUEENMOVES[0][d];
		nextCol = currentCol + i * QUEENMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		if (pieceStatus == OFF_BOARD) {
			continue;
		}

		while (pieceStatus == NO_PIECE) {
			bitAttackVector |= BitBoard::getMask(nextRow, nextCol);
			i++;
			nextRow = currentRow + i * QUEENMOVES[0][d];
			nextCol = currentCol + i * QUEENMOVES[1][d];
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
			nextRow = currentRow + i * QUEENMOVES[0][d];
			nextCol = currentCol + i * QUEENMOVES[1][d];
			pieceStatus = board->checkPiece(nextRow, nextCol, player);

			while (pieceStatus == NO_PIECE) {
				bitAttackCompliment |= BitBoard::getMask(nextRow, nextCol);
				i++;
				nextRow = currentRow + i * QUEENMOVES[0][d];
				nextCol = currentCol + i * QUEENMOVES[1][d];
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

Queen::~Queen() {
	// TODO Auto-generated destructor stub
}
}
