/*
 * Board.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Board.h"

namespace OhWordC {

Board::Board() {
	this->board = new Piece[8][8];

	this->pieces[WHITE] = new vector<Piece>();
	this->pieces[BLACK] = new vector<Piece>();

	this->piecesTaken[WHITE] = new vector<Piece>();
	this->piecesTaken[BLACK] = new vector<Piece>();

	this->moveHistory = new vector<Move>();
	this->hashCodeHistory = new vector<long>();
	this->rngTable = RNGTable::getSingleton();
	this->turn = WHITE;
	this->nullMoveInfo = new long[3];

	kings[BLACK] = new Piece(KING, BLACK, -1, -1, false);
	kings[WHITE] = new Piece(KING, WHITE, -1, -1, false);

	placePiece(kings[BLACK], 0, 0);
	placePiece(kings[WHITE], 7, 0);

}

Board::Board(vector<Piece>* pieces, side_t turn, vector<Move> moveHistory, int** rookStartCols, int* kingCols) {
	this->board = new Piece[8][8];
	this->pieces[WHITE] = new vector<Piece>(pieces[WHITE].size());
	this->pieces[BLACK] = new vector<Piece>(pieces[BLACK].size());

	this->piecesTaken[WHITE] = new vector<Piece>();
	this->piecesTaken[BLACK] = new vector<Piece>();

	this->moveHistory = new stack<Move>();
	this->hashCodeHistory = new stack<long>();
	this->rngTable = RNGTable::getSingleton();
	this->turn = turn;
	this->nullMoveInfo = new long[3];

	long** posBitBoard = new long[6][2];
	// long[] pawnPosBitboard = { 0, 0 };
	// long[] kingPosBitboard = { 0, 0 };

	int* pawnRow = new int[2];
	pawnRow[BLACK] = 1;
	pawnRow[WHITE] = 6;

	Piece temp;

	for (int i = 0; i < 2; i++) {

		for (int p = 0; p < pieces[i].size(); p++) {
			temp = pieces[i].at(p).getCopy();

			this->pieces[i].push_back(temp);

			board[temp.getRow()][temp.getCol()] = temp;

			posBitBoard[temp.getPieceID()][i] |= temp.getBit();

			if (temp.getPieceID() == PAWN) {

				if (temp.getRow() != pawnRow[i]) {
					temp.setMoved(true);
				}
			}

			if (temp.getPieceID() == KING) {

				kings[i] = temp;

				if (temp.getRow() != materialRow[i]) {
					temp.setMoved(true);
				}
			}
		}

	}

	this->posBitBoard = posBitBoard;

	for (int i = 0; i < 6; i++) {
		this->allPosBitBoard[0] |= posBitBoard[i][0];
		this->allPosBitBoard[1] |= posBitBoard[i][1];
	}

	this->hashCode = generateHashCode();

	if (moveHistory.size() > 0) {
		long move;
		side_t moveSide;
		if (moveHistory.size() % 2 == 0) {
			moveSide = turn;
		} else {
			moveSide = Side::otherSide(turn);
		}

		for (int i = 0; i < moveHistory.size(); i++) {
			move = moveHistory.back().getMoveLong();
			moveHistory.pop_back();

			this->moveHistory.push_back(*(new Move(move)));

			if (Move::hasPieceTaken(move)) {
				piecesTaken[Side::otherSide(moveSide)].push_back(
						*(new Piece(Move::getPieceTakenID(move), Side::otherSide(moveSide), Move::getPieceTakenRow(move), Move::getPieceTakenCol(move),
								Move::getPieceTakenHasMoved(move))));
			}

			moveSide = Side::otherSide(moveSide);
		}

	} else {
		loadPiecesTaken();
	}

	if (kingCols == 0 || rookStartCols == 0) {
		initializeCastleSetup();
	} else {
		this->kingCols = kingCols;
		this->rookStartCols = rookStartCols;
	}

	// this.castleRights = castleRights;
}

bool Board::makeMove(long move) {

	int fromRow = Move::getFromRow(move);
	int fromCol = Move::getFromCol(move);
	int toRow = Move::getToRow(move);
	int toCol = Move::getToCol(move);
	MoveNote note = Move::getNote(move);

	// save off hashCode
	hashCodeHistory.push_back(hashCode);

	// remove previous castle options
	hashCode ^= rngTable.getCastlingRightsRandom(this->farRookHasMoved(BLACK), this->nearRookHasMoved(BLACK), this->kingHasMoved(BLACK),
			this->farRookHasMoved(WHITE), this->nearRookHasMoved(WHITE), this->kingHasMoved(WHITE));

	// remove taken piece first
	if (Move::hasPieceTaken(move)) {

		Piece pieceTaken = board[Move::getPieceTakenRow(move)][Move::getPieceTakenCol(move)];

		// remove pieceTaken from vectors
		pieces[Side::otherSide(turn)].erase(find(pieces[Side::otherSide(turn)].begin(),pieces[Side::otherSide(turn)].end(),pieceTaken));

		// // remove bit position from appropriate side
		// allPosBitBoard[pieceTaken.getSide().ordinal()] ^=
		// pieceTaken.getBit();
		//
		// if (pieceTaken.getPieceID() == PieceID.PAWN) {
		// pawnPosBitBoard[pieceTaken.getSide().ordinal()] ^=
		// pieceTaken.getBit();
		//
		// }
		//
		// if (pieceTaken.getPieceID() == PieceID.KING) {
		// kingPosBitBoard[pieceTaken.getSide().ordinal()] ^=
		// pieceTaken.getBit();
		// }

		posBitBoard[pieceTaken.getPieceID()][pieceTaken.getSide()] ^= pieceTaken.getBit();
		allPosBitBoard[pieceTaken.getSide()] ^= pieceTaken.getBit();

		// remove ref to piecetaken on board
		board[pieceTaken.getRow()][pieceTaken.getCol()] = 0;

		// remove old hash from piece that was taken, if any
		hashCode ^= rngTable.getPiecePerSquareRandom(pieceTaken.getSide(), pieceTaken.getPieceID(), pieceTaken.getRow(), pieceTaken.getCol());

	}

	if (note == CASTLE_NEAR || note == CASTLE_FAR) {

		Piece king = kings[turn];
		Piece rook;

		if (note == CASTLE_NEAR) {
			rook = board[materialRow[turn]][rookStartCols[turn][1]];

			movePiece(king, materialRow[turn], 6, NONE);
			movePiece(rook, materialRow[turn], 5, NONE);

			board[materialRow[turn]][6] = king;
			board[materialRow[turn]][5] = rook;

			castleRights[turn] = 2;
		} else {
			rook = board[materialRow[turn]][rookStartCols[turn][0]];

			movePiece(king, materialRow[turn], 2, NONE);
			movePiece(rook, materialRow[turn], 3, NONE);

			board[materialRow[turn]][2] = king;
			board[materialRow[turn]][3] = rook;

			castleRights[turn] = 1;
		}

	} else {

		movePiece(board[fromRow][fromCol], toRow, toCol, note);

	}

	// if last move made is pawn leap, remove en passant file num
	if (getLastMoveMade() != 0) {
		if (Move::getNote(getLastMoveMade()) == PAWN_LEAP) {
			hashCode ^= rngTable.getEnPassantFile(Move::getToCol(getLastMoveMade()));
		}
	}

	// if new move is pawn leap, add en passant file num
	if (note == PAWN_LEAP) {
		hashCode ^= rngTable.getEnPassantFile(Move::getToCol(move));
	}

	// add new castle options
	hashCode ^= rngTable.getCastlingRightsRandom(this->farRookHasMoved(BLACK), this->nearRookHasMoved(BLACK), this->kingHasMoved(BLACK),
			this->farRookHasMoved(WHITE), this->nearRookHasMoved(WHITE), this->kingHasMoved(WHITE));

	// either remove black and add white or reverse. Same operation.
	hashCode ^= rngTable.getBlackToMoveRandom();

	// show that this move is now the last move made
	moveHistory.push_back(*(new Move(move)));

	// move was made, next player's turn
	turn = Side::otherSide(turn);

	// verifyBitBoards();

	return true;

}

void Board::movePiece(Piece pieceMoving, int toRow, int toCol, MoveNote note) {

	long bitMove = BitBoard::getMask(pieceMoving.getRow(), pieceMoving.getCol()) ^ BitBoard::getMask(toRow, toCol);

	// remove bit position from where piece was and add where it is now
	posBitBoard[pieceMoving.getPieceID()][pieceMoving.getSide()] ^= bitMove;
	allPosBitBoard[pieceMoving.getSide()] ^= bitMove;

	// remove old hash from where piece was
	hashCode ^= rngTable.getPiecePerSquareRandom(turn, pieceMoving.getPieceID(), pieceMoving.getRow(), pieceMoving.getCol());

	// remove pieces old position
	board[pieceMoving.getRow()][pieceMoving.getCol()] = 0;
	// update board to reflect piece's new position
	board[toRow][toCol] = pieceMoving;

	// tell piece its new position
	pieceMoving.setPos(toRow, toCol);
	pieceMoving.setMoved(true);

	if (note == NEW_QUEEN) {
		pieceMoving.setPieceID(QUEEN);
		posBitBoard[PAWN][pieceMoving.getSide()] ^= pieceMoving.getBit();
		posBitBoard[QUEEN][pieceMoving.getSide()] ^= pieceMoving.getBit();
	}

	// if (pieceMoving == getKing(turn)) {
	// setCastleRights(turn, 0);
	// }

	// add hash of piece at new location
	hashCode ^= rngTable.getPiecePerSquareRandom(turn, pieceMoving.getPieceID(), toRow, toCol);
}

long Board::undoMove() {

	// if no there is no last move then undoMove is impossible
	if (moveHistory.empty()) {
		// System.out.println("Can not undo move");
		return 0;
	}

	// retrieve last move made
	long lastMove = getLastMoveMade();

	int fromRow = Move::getFromRow(lastMove);
	int fromCol = Move::getFromCol(lastMove);
	int toRow = Move::getToRow(lastMove);
	int toCol = Move::getToCol(lastMove);
	MoveNote note = Move::getNote(lastMove);

	// last move made was made by previous player, which is also the next
	// player
	turn = Side::otherSide(turn);

	if (note == CASTLE_NEAR || note == CASTLE_FAR) {

		Piece king = kings[turn];
		Piece rook;

		if (note == CASTLE_FAR) {
			rook = board[materialRow[turn]][3];

			undoMovePiece(king, materialRow[turn], kingCols[turn], NONE, false);
			undoMovePiece(rook, materialRow[turn], rookStartCols[turn][0], NONE, false);

			board[materialRow[turn]][kingCols[turn]] = king;
			board[materialRow[turn]][rookStartCols[turn][0]] = rook;

		} else {

			rook = board[materialRow[turn]][5];

			undoMovePiece(king, materialRow[turn], kingCols[turn], NONE, false);
			undoMovePiece(rook, materialRow[turn], rookStartCols[turn][1], NONE, false);

			board[materialRow[turn]][kingCols[turn]] = king;
			board[materialRow[turn]][rookStartCols[turn][1]] = rook;

		}

		castleRights[turn] = 0;

	} else {
		undoMovePiece(board[toRow][toCol], fromRow, fromCol, note, Move::hadMoved(lastMove));
	}

	if (Move::hasPieceTaken(lastMove)) {

		// add taken piece back to vectors and board
		Piece pieceTaken = piecesTaken[Side::otherSide(turn)].pop_back()();

		pieces[Side::otherSide(turn)].push_back(pieceTaken);

		// add piece taken to position bit board
		posBitBoard[pieceTaken.getPieceID()][pieceTaken.getSide()] |= pieceTaken.getBit();
		allPosBitBoard[pieceTaken.getSide()] |= pieceTaken.getBit();

		board[pieceTaken.getRow()][pieceTaken.getCol()] = pieceTaken;

	}

	// move was undone so show move made before that as the last move made
	moveHistory.pop_back();

	if (hashCodeHistory.empty()) {
		// if no hashCode was saved then generate it the hard way
		hashCode = generateHashCode();
	} else {
		// retrieve what the hashCode was before move was made
		hashCode = hashCodeHistory.pop_back();
	}

	// verifyBitBoards();

	return lastMove;

}

void Board::undoMovePiece(Piece pieceMoving, int fromRow, int fromCol, MoveNote note, bool hadMoved) {

	long bitMove = BitBoard::getMask(pieceMoving.getRow(), pieceMoving.getCol()) ^ BitBoard::getMask(fromRow, fromCol);

	// remove bit position from where piece was and add where it is now
	posBitBoard[pieceMoving.getPieceID()][pieceMoving.getSide()] ^= bitMove;
	allPosBitBoard[pieceMoving.getSide()] ^= bitMove;

	// remove old position
	board[pieceMoving.getRow()][pieceMoving.getCol()] = 0;
	// put piece in old position
	board[fromRow][fromCol] = pieceMoving;

	// tell piece where it was
	pieceMoving.setPos(fromRow, fromCol);

	// show whether piece had moved before this move was made
	pieceMoving.setMoved(hadMoved);

	if (note == NEW_QUEEN) {
		pieceMoving.setPieceID(PAWN);
		posBitBoard[PAWN][pieceMoving.getSide()] |= pieceMoving.getBit();
		posBitBoard[QUEEN][pieceMoving.getSide()] ^= pieceMoving.getBit();
	}

}

void Board::verifyBitBoards() {

	Piece piece;

	long** allBitBoard = new long[6][2];

	for (int i = 0; i < 6; i++) {
		allBitBoard[i][0] = posBitBoard[i][0];
		allBitBoard[i][1] = posBitBoard[i][1];
	}

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			piece = board[r][c];

			if (piece != 0) {
				allBitBoard[piece.getPieceID()][piece.getSide()] ^= BitBoard::getMask(r, c);
			}

		}
	}

	for (int i = 0; i < 6; i++) {
		if (allBitBoard[i][0] != 0) {
			printf("BitBoard Problem!!!");
		}

		if (allBitBoard[i][1] != 0) {
			printf("BitBoard Problem!!!");
		}
	}

}

bool Board::canUndo() {
	return (moveHistory.size() != 0);
}

vector<long> Board::generateValidMoves() {
	return generateValidMoves(false, 0, { 0 });
}

vector<long> Board::generateValidMoves(bool sort, long hashMove, long* killerMoves) {

	// find in check details. i.e. left and right castle info
	// makeNullMove();

	// System.out.println("Not safe areas");
	// BitBoard.printBitBoard(nullMoveInfo[0]);
	//
	// System.out.println("in check vector");
	// BitBoard.printBitBoard(nullMoveInfo[1]);

	// ArrayList<Long> validMoves = new ArrayList<Long>(50);
	validMoves.clear();

	if (!hasSufficientMaterial() || drawByThreeRule()) {
		setBoardStatus(DRAW);
		return validMoves;
	}

	int prevMovesSize = 0;

	long move;
	for (int p = 0; p < pieces[turn].size(); p++) {

		pieces[turn].at(p).generateValidMoves(this, nullMoveInfo, allPosBitBoard, validMoves);

		for (int m = prevMovesSize; m < validMoves.size(); m++) {
			move = validMoves.at(m);

			move = Move::setHadMoved(move, pieces[turn].at(p).hasMoved());

//			if (move == hashMove) {
//				move = Move::setValue(move, 10000);
//				validMoves.insert(validMoves.begin(), m, move);
//				continue;
//			}
//
//			for (int k = 0; k < killerMoves.length; k++) {
//				if (move == killerMoves[k]) {
//					move = Move::setValue(move, 9999 - k);
//					break;
//				}
//			}

			validMoves.data()[m] = move;

		}

		prevMovesSize = validMoves.size();

	}

//	if (sort) {
//		Collections.sort(validMoves, Collections.reverseOrder());
//	}

	if (validMoves.size() == 0) {
		if (isInCheck()) {
			setBoardStatus(CHECKMATE);
		} else {
			setBoardStatus(STALEMATE);
		}
	}

	return validMoves;
}

long* Board::makeNullMove() {
	// long nullMoveAttacks = 0;
	// long inCheckVector = BitBoard.ALL_ONES;
	// long bitAttackCompliment = 0;
	//
	// nullMoveInfo[0] = nullMoveAttacks;
	// nullMoveInfo[1] = inCheckVector;
	// nullMoveInfo[2] = bitAttackCompliment;

	// recalculating check info
	clearBoardStatus();

	for (int p = 0; p < pieces[turn].size(); p++) {
		pieces[turn].at(p).clearBlocking();
	}

	nullMoveInfo[0] = BitBoard::getPawnAttacks(posBitBoard[PAWN][Side::otherSide(turn)], Side::otherSide(turn));
	nullMoveInfo[0] |= BitBoard::getKnightAttacks(posBitBoard[KNIGHT][Side::otherSide(turn)]);
	nullMoveInfo[0] |= BitBoard::getKingAttacks(posBitBoard[KING][Side::otherSide(turn)]);

	nullMoveInfo[1] = BitBoard::getPawnAttacks(posBitBoard[KING][turn], turn) & posBitBoard[PAWN][Side::otherSide(turn)];

	nullMoveInfo[1] |= BitBoard::getKnightAttacks(posBitBoard[KING][turn]) & posBitBoard[KNIGHT][Side::otherSide(turn)];

	if (nullMoveInfo[1] == 0) {
		nullMoveInfo[1] = -1;
	}

	nullMoveInfo[2] = 0;

	long updown = ~(allPosBitBoard[0] | allPosBitBoard[1]);
	long left = 0xFEFEFEFEFEFEFEFEL & updown;
	long right = 0x7F7F7F7F7F7F7F7FL & updown;

	for (int p = 0; p < pieces[Side::otherSide(turn)].size(); p++) {

		pieces[Side::otherSide(turn)].at(p).getNullMoveInfo(this, nullMoveInfo, updown, left, right, posBitBoard[KING][turn],
				King::getKingCheckVectors(posBitBoard[KING][turn], updown, left, right), allPosBitBoard[turn]);

	}

	// for (int i = 0; i < 3; i++) {
	// System.out.println(BitBoard.printBitBoard(nullMoveInfo[i]));
	// }

	if ((kings[turn].getBit() & nullMoveInfo[0]) != 0) {
		setBoardStatus(CHECK);
	}

	return nullMoveInfo;

}

PositionStatus Board::checkPiece(int row, int col, side_t player) {

	if (((row | col) & (~0x7)) != 0) {
		return OFF_BOARD;
	}

	if (board[row][col] != 0) {
		if (board[row][col].getSide() == player)
			return FRIEND;
		else
			return ENEMY;
	} else {
		return NO_PIECE;
	}

}

long Board::getLastMoveMade() {
	if (!moveHistory.empty()) {
		return moveHistory.back().getMoveLong();
	} else {
		return 0;
	}
}

vector<Move> Board::getMoveHistory() {
	return moveHistory;
}

int Board::getPieceValue(int row, int col) {
	return Values::getPieceValue(board[row][col].getPieceID()) + getOpeningPositionValue(board[row][col]);
}

int Board::getOpeningPositionValue(Piece piece) {

	if (piece == 0) {
		return 0;
	}

	int value;
	side_t player = piece.getSide();
	int row = piece.getRow();
	int col = piece.getCol();

	switch (piece.getPieceID()) {
	case KNIGHT:
		value = PositionBonus::getKnightPositionBonus(row, col, player);
		break;
	case PAWN:
		value = PositionBonus::getPawnPositionBonus(row, col, player);
		break;
	case BISHOP:
		value = 0;
		break;
	case KING:
		value = 0;
		value = PositionBonus::getKingOpeningPositionBonus(row, col, player);
		break;
	case QUEEN:
		value = 0;
		break;
	case ROOK:
		value = PositionBonus::getRookBonus(row, col);
		break;
	default:
		value = 0;
		printf("Error: invalid piece value request!");
	}

	return value;

}

int Board::getEndGamePositionValue(Piece piece) {
	int value;
	side_t player = piece.getSide();
	int row = piece.getRow();
	int col = piece.getCol();

	switch (piece.getPieceID()) {
	case KNIGHT:
		value = PositionBonus::getKnightPositionBonus(row, col, player);
		break;
	case PAWN:
		value = PositionBonus::getPawnPositionBonus(row, col, player);
		break;
	case BISHOP:
		value = 50;
		break;
	case KING:
		value = PositionBonus::getKingEndGamePositionBonus(row, col, player);
		break;
	case QUEEN:
		value = 100;
		break;
	case ROOK:
		value = PositionBonus::getRookBonus(row, col);
		break;
	default:
		value = 0;
		printf("Error: invalid piece value request!");
	}

	return value;

}

int Board::openingPositionScore(side_t side) {
	int score = 0;

	for (int i = 0; i < pieces[side].size(); i++) {
		score += getOpeningPositionValue(pieces[side].at(i));
	}

	return score;
}

int Board::endGamePositionScore(side_t side) {
	int score = 0;

	for (int i = 0; i < pieces[side].size(); i++) {
		score += getEndGamePositionValue(pieces[side].at(i));
	}

	return score;
}

int Board::materialScore(side_t side) {
	int score = 0;

	for (int i = 0; i < pieces[side].size(); i++) {
		score += Values::getPieceValue(pieces[side].at(i).getPieceID());
	}

	return score;
}

int Board::castleScore(side_t side) {
	int score = 0;
	int castleRights = this->castleRights[side];

	if (castleRights != 0) {
		if (castleRights == 1) {
			score += Values::FAR_CASTLE_VALUE;
		} else {
			score += Values::NEAR_CASTLE_VALUE;
		}
	} else {
		if (!kingHasMoved(side)) {
			if (farRookHasMoved(side)) {
				score -= Values::FAR_CASTLE_ABILITY_LOST_VALUE;
			}

			if (nearRookHasMoved(side)) {
				score -= Values::NEAR_CASTLE_ABILITY_LOST_VALUE;
			}
		} else {
			score -= Values::CASTLE_ABILITY_LOST_VALUE;
		}
	}

	return score;
}

int Board::pawnStructureScore(side_t side, int phase) {

	long pawns = posBitBoard[PAWN][side];
	long otherPawns = posBitBoard[PAWN][Side::otherSide(side)];

	int occupiedCol = 0;
	int passedPawns = 0;
	for (int c = 0; c < 8; c++) {
		if ((BitBoard::getColMask(c) & pawns) != 0) {
			occupiedCol++;
			if ((BitBoard::getColMask(c) & otherPawns) == 0) {
				passedPawns++;
			}
		}
	}

	int doubledPawns = BitBoard::count_bits(pawns) - occupiedCol;

	return BitBoard::getBackedPawns(pawns) * Values::BACKED_PAWN_BONUS + doubledPawns * Values::DOUBLED_PAWN_BONUS
			+ ((passedPawns * Values::PASSED_PAWN_BONUS * phase) / 256);
}

int Board::calcGamePhase() {

	int phase = Values::TOTALPHASE;

	for (int i = 0; i < 2; i++) {
		for (int p = 0; p < pieces[i].size(); p++) {
			phase -= Values::PIECE_PHASE_VAL[pieces[i].at(p).getPieceID()];
		}
	}

	phase = (phase * 256 + (Values::TOTALPHASE / 2)) / Values::TOTALPHASE;

	return phase;
}

int Board::staticScore() {
	int ptDiff = 0;

	int phase = calcGamePhase();

	int myPawnScore = pawnStructureScore(turn, phase);
	int yourPawnScore = pawnStructureScore(Side::otherSide(turn), phase);

	int openingMyScore = castleScore(turn) + openingPositionScore(turn);
	int openingYourScore = castleScore(Side::otherSide(turn)) + openingPositionScore(Side::otherSide(turn));

	int endGameMyScore = endGamePositionScore(turn);
	int endGameYourScore = endGamePositionScore(Side::otherSide(turn));

	int myScore = (openingMyScore * (256 - phase) + endGameMyScore * phase) / 256 + materialScore(turn) + myPawnScore;
	int yourScore = (openingYourScore * (256 - phase) + endGameYourScore * phase) / 256 + materialScore(Side::otherSide(turn)) + yourPawnScore;

	ptDiff = myScore - yourScore;

	return ptDiff;
}

Piece Board::getPiece(int row, int col) {
	return board[row][col];
}

PieceID Board::getPieceID(int row, int col) {
	if (board[row][col] != 0) {
		return board[row][col].getPieceID();
	} else {
		return 0;
	}

}

side_t Board::getPieceSide(int row, int col) {
	if (board[row][col] != 0) {
		return board[row][col].getSide();
	} else {
		printf("Error: requested player on null piece");
		return 0;
	}

}

side_t Board::getTurn() {
	return turn;
}

void Board::setTurn(side_t turn) {
	this->turn = turn;
}

bool Board::hasPiece(int row, int col) {
	if ((row & ~0x7) != 0 || (col & ~7) != 0) {
		return false;
	} else {
		return (board[row][col] != 0);
	}
}

bool Board::hasMoved(int row, int col) {
	if (hasPiece(row, col)) {
		return board[row][col].hasMoved();
	} else {
		return true;
	}
}

vector<Piece> Board::getPiecesTakenFor(side_t player) {
	return piecesTaken[player];
}

void Board::initializeCastleSetup() {

	int** rookCols = { { -1, -1 }, { -1, -1 } };
	this->rookStartCols = rookCols;

	for (int s = 0; s < 2; s++) {
		for (int c = kings[s].getCol() - 1; c >= 0; c--) {

			if (board[materialRow[s]][c] != 0) {
				if (board[materialRow[s]][c].getPieceID() == ROOK) {
					rookCols[s][0] = c;
					break;
				}
			}
		}

		for (int c = kings[s].getCol() + 1; c < 8; c++) {
			if (board[materialRow[s]][c] != 0) {
				if (board[materialRow[s]][c].getPieceID() == ROOK) {
					rookCols[s][1] = c;
					break;
				}
			}
		}
	}

	kingCols[BLACK] = kings[BLACK].getCol();
	kingCols[WHITE] = kings[WHITE].getCol();

}

bool Board::placePiece(Piece piece, int toRow, int toCol) {

	if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8) {
		if (board[toRow][toCol] != 0) {
			if (board[toRow][toCol].getPieceID() == KING) {
				return false;
			}
		}
	}

	if (piece.getPieceID() == KING) {
		if (toRow < 0 || toCol < 0) {
			return false;
		} else {
			kings[piece.getSide()] = piece;
		}
	}

	piece.setMoved(false);

	if (piece.getRow() >= 0) {
		// remove where piece was if it was on board
		posBitBoard[piece.getPieceID()][piece.getSide()] ^= piece.getBit();
		allPosBitBoard[piece.getSide()] ^= piece.getBit();
		board[piece.getRow()][piece.getCol()] = 0;

	} else {

		pieces[piece.getSide()].push_back(piece);
	}

	if (toRow >= 0) {
		// remove where piece taken was
		if (board[toRow][toCol] != 0) {

			Piece pieceTaken = board[toRow][toCol];

			// remove bit position of piece taken
			posBitBoard[pieceTaken.getPieceID()][pieceTaken.getSide()] ^= pieceTaken.getBit();
			allPosBitBoard[pieceTaken.getSide()] ^= pieceTaken.getBit();

			// remove ref to piece taken
			pieces[pieceTaken.getSide()].erase(find(pieces[pieceTaken.getSide()].begin(),pieces[pieceTaken.getSide()].end(),pieceTaken));
		}

		// tell piece where it is now
		piece.setPos(toRow, toCol);

		// reflect new piece in position bitboard
		posBitBoard[piece.getPieceID()][piece.getSide()] |= piece.getBit();
		allPosBitBoard[piece.getSide()] |= piece.getBit();

		// update board ref to show piece there
		board[toRow][toCol] = piece;
	} else {
		// piece is being taken off the board. Remove
		if (piece.getPieceID() != KING) {
			pieces[piece.getSide()].erase(find(pieces[piece.getSide()].begin(),pieces[piece.getSide()].end(),piece));
		}
	}

	// basically start over with new board
	this->moveHistory.clear();
	this->hashCodeHistory.clear();

	this->hashCode = generateHashCode();

	initializeCastleSetup();

	verifyBitBoards();

	return true;

}

bool Board::isInCheck() {
	return (boardStatus == CHECK);
}

bool Board::isInCheckMate() {
	return (boardStatus == CHECKMATE);
}

bool Board::isInStaleMate() {
	return (boardStatus == STALEMATE);
}

bool Board::isTimeUp() {
	return (boardStatus == TIMES_UP);
}

bool Board::isDraw() {
	return (boardStatus == DRAW);
}

bool Board::isInvalid() {
	return (boardStatus == INVALID);
}

bool Board::isGameOver() {
	return (isInCheckMate() || isInStaleMate() || isTimeUp() || isDraw() || isInvalid());
}

void Board::clearBoardStatus() {
	boardStatus = IN_PLAY;
}

GameStatus Board::getBoardStatus() {
	return boardStatus;
}

void Board::setBoardStatus(GameStatus boardStatus) {
	this->boardStatus = boardStatus;
}

bool Board::farRookHasMoved(side_t player) {
	return hasMoved(materialRow[player], rookStartCols[player][0]);
}

bool Board::nearRookHasMoved(side_t player) {
	return hasMoved(materialRow[player], rookStartCols[player][1]);
}

int Board::getRookStartingCol(side_t side, int near) {
	return rookStartCols[side][near];
}

int Board::getKingStartingCol(side_t side) {
	return kingCols[side];
}

bool Board::kingHasMoved(side_t player) {
	return kings[player].hasMoved();
}

long Board::farCastleMask(side_t player) {
	return BitBoard::getCastleMask(Math::min(rookStartCols[player][0], 2), kings[player].getCol(), player);
}

long Board::nearCastleMask(side_t player) {
	return BitBoard::getCastleMask(kings[player].getCol(), Math::max(rookStartCols[player][1], 6), player);
}

Board Board::getCopy() {
	return new Board(pieces, this->turn, moveHistory, rookStartCols, kingCols);
}

//string Board::toString() {
//	string stringBoard = "";
//	int pieceDetails = 0;
//	Piece p;
//
//	for (int row = 0; row < 8; row++) {
//		for (int col = 0; col < 8; col++) {
//			if (board[row][col] != 0) {
//
//				p = board[row][col];
//
//				if (p.hasMoved() && (p.getPieceID() == PAWN || p.getPieceID() == KING || p.getPieceID() == ROOK)) {
//					pieceDetails |= 1;
//				}
//
//				if (p.getPieceID() == ROOK && kingHasMoved(p.getSide())) {
//					pieceDetails |= 1;
//				}
//
//				if (p.getPieceID() == KING && nearRookHasMoved(p.getSide()) && farRookHasMoved(p.getSide())) {
//					pieceDetails |= 1;
//				}
//
//				long lastMove = getLastMoveMade();
//
//				if (getLastMoveMade() != 0) {
//					if (Move::getToRow(lastMove) == row && Move::getToCol(lastMove) == col && Move::getNote(lastMove) == MoveNote::PAWN_LEAP) {
//						pieceDetails |= 2;
//					}
//				}
//
//				stringBoard += board[row][col].toString() + pieceDetails + ",";
//				pieceDetails = 0;
//
//			} else {
//				stringBoard += "__,";
//			}
//
//		}
//		stringBoard += "\n";
//	}
//
//	return stringBoard;
//}

//string Board::toXML(bool includeHistory) {
//	string xmlBoard = "<board>\n";
//
//	if (includeHistory) {
//
//		vector<Move> movesToRedo = new vector<Move>();
//		long m;
//		while ((m = undoMove()) != 0) {
//			movesToRedo.push_back(*(new Move(m)));
//		}
//
//		xmlBoard += "<setup>\n" + this.toString() + "</setup>\n";
//		xmlBoard += "<turn>" + turn.toString() + "</turn>\n";
//
//		while (!movesToRedo.empty()) {
//			makeMove(movesToRedo.pop_back().getMoveLong());
//		}
//
//		for (int i = 0; i < moveHistory.size(); i++) {
//			xmlBoard += Move::toXML(moveHistory.at(i).getMoveLong());
//		}
//
//	} else {
//		xmlBoard += "<setup>\n" + this.toString() + "</setup>\n";
//		xmlBoard += "<turn>" + turn.toString() + "</turn>\n";
//	}
//
//	xmlBoard += "</board>";
//	return xmlBoard;
//}

long Board::generateHashCode() {
	long hashCode = 0;

	if (turn == BLACK) {
		hashCode = rngTable.getBlackToMoveRandom();
	}

	Piece p;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			p = board[r][c];
			if (p != 0) {
				hashCode ^= rngTable.getPiecePerSquareRandom(p.getSide(), p.getPieceID(), r, c);
			}
		}
	}

	hashCode ^= rngTable.getCastlingRightsRandom(this->farRookHasMoved(BLACK), this->nearRookHasMoved(BLACK), this->kingHasMoved(BLACK),
			this->farRookHasMoved(WHITE), this->nearRookHasMoved(WHITE), this->kingHasMoved(WHITE));

	if (getLastMoveMade() != 0) {
		if (Move::getNote(getLastMoveMade()) == PAWN_LEAP) {
			hashCode ^= rngTable.getEnPassantFile(Move::getToCol(getLastMoveMade()));
		}
	}

	return hashCode;
}

//int Board::getHashIndex() {
//	return (int) (hashCode & AISettings.hashIndexMask);
//}

long Board::getHashCode() {
	return hashCode;
}

//static long Board::getHashCode(string xmlBoard) {
//	Board board = XMLParser.XMLToBoard(xmlBoard);
//
//	if (board != 0) {
//		return board.getHashCode();
//	} else {
//		return 0;
//	}
//}

bool Board::drawByThreeRule() {

	int count = 0;
	int fiftyMove = 0;

	for (int i = hashCodeHistory.size() - 1; i >= 0; i--) {

		if (fiftyMove >= 101) {
			return true;
		}

		if (hashCode == hashCodeHistory.at(i)) {
			count++;
		}

		if (count > 2) {
			return true;
		}

		if (moveHistory.at(i).hasPieceTaken()) {
			return false;
		}

		fiftyMove++;
	}

	return false;
}

bool Board::hasSufficientMaterial() {

	bool sufficient = true;

	if (pieces[0].size() <= 2 && pieces[1].size() <= 2) {

		sufficient = false;

		for (int i = 0; i < 2; i++) {
			for (int p = 0; p < pieces[i].size(); p++) {
				if ((pieces[i].at(p).getPieceID() == PAWN) || (pieces[i].at(p).getPieceID() == QUEEN) || (pieces[i].at(p).getPieceID() == ROOK)) {
					sufficient = true;
				}
			}
		}

	}

	return sufficient;
}

void Board::loadPiecesTaken() {

	for (int i = 0; i < 2; i++) {

		piecesTaken[i] = getFullPieceSet((side_t) i);

		Piece piecePresent;
		for (int p = 0; p < pieces[i].size(); p++) {
			piecePresent = pieces[i].at(p);

			for (int t = 0; t < piecesTaken[i].size(); t++) {
				if (piecesTaken[i].at(t).getPieceID() == piecePresent.getPieceID()) {
					piecesTaken[i].erase(piecesTaken[i].begin() + t);
					break;
				}
			}
		}
	}

}

static vector<Piece> Board::getFullPieceSet(side_t player) {
	vector<Piece> pieces = new vector<Piece>();

	for (int i = 0; i < 8; i++) {
		pieces.push_back(*(new Piece(PAWN, player, 0, 0, false)));
	}

	for (int i = 0; i < 2; i++) {
		pieces.push_back(*(new Piece(BISHOP, player, 0, 0, false)));
	}

	for (int i = 0; i < 2; i++) {
		pieces.push_back(*(new Piece(ROOK, player, 0, 0, false)));
	}

	for (int i = 0; i < 2; i++) {
		pieces.push_back(*(new Piece(KNIGHT, player, 0, 0, false)));
	}

	pieces.push_back(*(new Piece(KING, player, 0, 0, false)));
	pieces.push_back(*(new Piece(QUEEN, player, 0, 0, false)));

	return pieces;
}

}

