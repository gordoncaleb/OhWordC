/*
 * King.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "King.h"

namespace OhWordC {
King::King() {
	// TODO Auto-generated constructor stub

}

static PieceID King::getPieceID() {
	return KING;
}

static string King::getName() {
	return "King";
}

static string King::getStringID() {
	return "K";
}

static void King::generateMoves(Piece* p, Board* board, vector<long> moves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int nextRow;
	int nextCol;
	PositionStatus pieceStatus;

	int moveVal = 0;
	if (!p->hasMoved() && (!board->farRookHasMoved(player) || !board->nearRookHasMoved(player))) {
		moveVal = Values::CASTLE_ABILITY_LOST_VALUE;
	}

	for (int d = 0; d < 8; d++) {
		nextRow = currentRow + KINGMOVES[0][d];
		nextCol = currentCol + KINGMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		if (pieceStatus ==NO_PIECE) {
			moves.push_back(Move::moveLong(currentRow, currentCol, nextRow, nextCol, moveVal, NONE));
		}

		if (pieceStatus == ENEMY) {
			moves.push_back(Move::moveLong(currentRow, currentCol, nextRow, nextCol, board->getPieceValue(nextRow, nextCol) + moveVal, NONE, board->getPiece(nextRow, nextCol)));
		}

	}

	// long allPosBitBoard = posBitBoard[0] | posBitBoard[1];
	//
	// if (!board.isInCheck()) {
	// // add possible castle move
	// if (canCastleFar(p, board, player, nullMoveInfo, allPosBitBoard)) {
	// if (isValidMove(currentRow, 2, nullMoveInfo)) {
	// if (currentCol > 3) {
	// validMoves.add(Move.moveLong(currentRow, currentCol, currentRow, 2,
	// Values.FAR_CASTLE_VALUE, MoveNote.CASTLE_FAR));
	// } else {
	// validMoves.add(Move.moveLong(currentRow,
	// board.getRookStartingCol(player, 0), currentRow, 3,
	// Values.FAR_CASTLE_VALUE,
	// MoveNote.CASTLE_FAR));
	// }
	// }
	// }
	//
	// if (canCastleNear(p, board, player, nullMoveInfo, allPosBitBoard)) {
	// if (isValidMove(currentRow, 6, nullMoveInfo)) {
	// if (currentCol < 5) {
	// validMoves.add(Move.moveLong(currentRow, currentCol, currentRow, 6,
	// Values.NEAR_CASTLE_VALUE, MoveNote.CASTLE_NEAR));
	// } else {
	// validMoves.add(Move.moveLong(currentRow,
	// board.getRookStartingCol(player, 1), currentRow, 5,
	// Values.NEAR_CASTLE_VALUE,
	// MoveNote.CASTLE_NEAR));
	// }
	// }
	// }
	// }
}

static vector<long> King::generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {
	int currentRow = p->getRow();
	int currentCol = p->getCol();
	side_t player = p->getSide();
	int nextRow;
	int nextCol;
	PositionStatus pieceStatus;
	long moveLong;

	for (int d = 0; d < 8; d++) {
		nextRow = currentRow + KINGMOVES[0][d];
		nextCol = currentCol + KINGMOVES[1][d];
		pieceStatus = board->checkPiece(nextRow, nextCol, player);

		if (pieceStatus == NO_PIECE) {

			if (isValidMove(nextRow, nextCol, nullMoveInfo)) {
				if (!p->hasMoved() && (!board->farRookHasMoved(player) || !board->nearRookHasMoved(player))) {
					// The player loses points for losing the ability to
					// castle
					moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, Values::CASTLE_ABILITY_LOST_VALUE);
				} else {
					moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, 0, NONE);
				}

				validMoves.push_back(moveLong);
			}
		}

		if (pieceStatus == ENEMY) {
			if (isValidMove(nextRow, nextCol, nullMoveInfo)) {
				moveLong = Move::moveLong(currentRow, currentCol, nextRow, nextCol, board->getPieceValue(nextRow, nextCol), NONE,
						board->getPiece(nextRow, nextCol));
				validMoves.push_back(moveLong);
			}
		}

	}

	long allPosBitBoard = posBitBoard[0] | posBitBoard[1];

	if (!board->isInCheck()) {
		// add possible castle move
		if (canCastleFar(p, board, player, nullMoveInfo, allPosBitBoard)) {
			if (isValidMove(currentRow, 2, nullMoveInfo)) {
				if (currentCol > 3) {
					validMoves.push_back(Move::moveLong(currentRow, currentCol, currentRow, 2, Values::FAR_CASTLE_VALUE, CASTLE_FAR));
				} else {
					validMoves.push_back(Move::moveLong(currentRow, board->getRookStartingCol(player, 0), currentRow, 3, Values::FAR_CASTLE_VALUE,
							CASTLE_FAR));
				}
			}
		}

		if (canCastleNear(p, board, player, nullMoveInfo, allPosBitBoard)) {
			if (isValidMove(currentRow, 6, nullMoveInfo)) {
				if (currentCol < 5) {
					validMoves.push_back(Move::moveLong(currentRow, currentCol, currentRow, 6, Values::NEAR_CASTLE_VALUE, CASTLE_NEAR));
				} else {
					validMoves.push_back(Move::moveLong(currentRow, board->getRookStartingCol(player, 1), currentRow, 5, Values::NEAR_CASTLE_VALUE,
		CASTLE_NEAR));
				}
			}
		}
	}

	return validMoves;

}

static void King::getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo) {

	int currentRow = p->getRow();
	int currentCol = p->getCol();

	for (int i = 0; i < 8; i++) {
		if (board->checkPiece(currentRow + KINGMOVES[0][i], currentCol + KINGMOVES[1][i], p->getSide()) != OFF_BOARD) {
			nullMoveInfo[0] |= BitBoard::getMask(currentRow + KINGMOVES[0][i], currentCol + KINGMOVES[1][i]);
		}
	}

}

static long King::getKingCheckVectors(long king, long updown, long left, long right){
	unsigned long temp = king;

	unsigned long checkVectors = king;

	// up
	while ((temp = (temp >> 8 & updown)) != 0) {
		checkVectors |= temp;
	}

	temp = king;

	// down
	while ((temp = (temp << 8 & updown)) != 0) {
		checkVectors |= temp;
	}

	temp = king;

	// going left
	if ((king & 0x0101010101010101L) == 0) {

		while ((temp = (temp >> 1 & left)) != 0) {
			checkVectors |= temp;
		}

		temp = king;

		while ((temp = (temp >> 9 & left)) != 0) {
			checkVectors |= temp;
		}

		temp = king;

		while ((temp = (temp << 7 & left)) != 0) {
			checkVectors |= temp;
		}

		temp = king;

	}

	// going right
	if ((king & 0x8080808080808080L) == 0) {

		while ((temp = (temp << 1 & right)) != 0) {
			checkVectors |= temp;
		}

		temp = king;

		while ((temp = (temp >> 7 & right)) != 0) {
			checkVectors |= temp;
		}

		temp = king;

		while ((temp = (temp << 9 & right)) != 0) {
			checkVectors |= temp;
		}

	}

	return checkVectors;
}

static bool King::isValidMove(int toRow, int toCol, long* nullMoveInfo) {
	long mask = BitBoard::getMask(toRow, toCol);

	// String nullmove0 = BitBoard.printBitBoard(nullMoveInfo[0]);
	// String nullmove1 = BitBoard.printBitBoard(nullMoveInfo[1]);
	// String nullmove2 = BitBoard.printBitBoard(nullMoveInfo[2]);

	if ((mask & (nullMoveInfo[0] | nullMoveInfo[2])) == 0) {
		return true;
	} else {
		return false;
	}
}

static bool King::canCastleFar(Piece* king, Board* board, side_t player, long* nullMoveInfo, long allPosBitBoard) {

	if (board->kingHasMoved(player) || board->farRookHasMoved(player)) {
		return false;
	}

	long kingToCastleMask = BitBoard::getCastleMask(king->getCol(), 2, player);

	int rookCol = board->getRookStartingCol(player, 0);
	long rookToCastleMask = BitBoard::getCastleMask(rookCol, 3, player);

	allPosBitBoard ^= BitBoard::getMask(king->getRow(), rookCol) | king->getBit();

	if ((kingToCastleMask & nullMoveInfo[0]) == 0) {
		if (((kingToCastleMask | rookToCastleMask) & allPosBitBoard) == 0) {
			return true;
		}
	}

	return false;

}

static bool King::canCastleNear(Piece* king, Board* board, side_t player, long* nullMoveInfo, long allPosBitBoard) {

	if (board->kingHasMoved(player) || board->nearRookHasMoved(player)) {
		return false;
	}

	long kingToCastleMask = BitBoard::getCastleMask(king->getCol(), 6, player);

	int rookCol = board->getRookStartingCol(player, 1);
	long rookToCastleMask = BitBoard::getCastleMask(rookCol, 5, player);

	allPosBitBoard ^= BitBoard::getMask(king->getRow(), rookCol) | king->getBit();

	// System.out.println(BitBoard.printBitBoard(kingToCastleMask));
	// System.out.println(BitBoard.printBitBoard(rookToCastleMask));
	// System.out.println(BitBoard.printBitBoard(allPosBitBoard));

	if ((kingToCastleMask & nullMoveInfo[0]) == 0) {
		if (((kingToCastleMask | rookToCastleMask) & allPosBitBoard) == 0) {
			return true;
		}
	}

	return false;
}

King::~King() {
	// TODO Auto-generated destructor stub
}
}

