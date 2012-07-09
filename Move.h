/*
 * Move.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "stdafx.h"


using namespace std;
namespace OhWordC {
enum MoveNote {
	NONE, CASTLE_NEAR, CASTLE_FAR, NEW_QUEEN, ENPASSANT, PAWN_LEAP
};

class Move {

	static int hadMovedMask;
	static int hasPieceTakenMask;
	static int pieceTakenHasMoved ;
	static int fromToMask;
	static int fromMask;
	static int toMask;
	static int notNoteMask;
	static int notPieceTaken;

	long move;

public:
	Move(long moveInt);
	Move(int fromRow, int fromCol, int toRow, int toCol);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved);

	static long moveLong(int fromRow, int fromCol, int toRow, int toCol);
	static long moveLong(int fromRow, int fromCol, int toRow, int toCol, int value);
	static long moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note);
	static long moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken);
	static long moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved);

	bool equals(Move move);
	static bool equals(long moveLongA, long moveLongB);
	static bool fromEquals(long moveLongA, long moveLongB);
	static bool toEquals(long moveLongA, long moveLongB);
	long setNote(MoveNote note);
	static long setNote(long moveLong, MoveNote note);
	MoveNote getNote();
	static MoveNote getNote(long moveLong);
	int getFromRow();
	static int getFromRow(long moveLong);
	int getFromCol();
	static int getFromCol(long moveLong);
	int getToRow();
	static int getToRow(long moveLong);
	int getToCol();
	static int getToCol(long moveLong);
	int getValue();
	static int getValue(long moveLong);
	long setValue(int value);
	static long setValue(long moveLong, int value);
	long setPieceTaken(Piece pieceTaken);
	static long setPieceTaken(long moveLong, Piece pieceTaken);
	bool hadMoved();
	static bool hadMoved(long moveLong);
	long setHadMoved(bool hadMoved);
	static long setHadMoved(long moveLong, bool hadMoved);
	bool hasPieceTaken();
	static bool hasPieceTaken(long moveLong);
	bool getPieceTakenHasMoved();
	static bool getPieceTakenHasMoved(long moveLong);
	int getPieceTakenRow();
	static int getPieceTakenRow(long moveLong);
	int getPieceTakenCol();
	static int getPieceTakenCol(long moveLong);
	PieceID getPieceTakenID();
	static PieceID getPieceTakenID(long moveLong);
	Move getCopy();
	long getMoveLong();

	virtual ~Move();
};

 int Move::hadMovedMask = 1 << 15;
 int Move::hasPieceTakenMask = 1 << 16;
 int Move::pieceTakenHasMoved = 1 << 26;
 int Move::fromToMask = 0xFFF;
 int Move::fromMask = 0xFC0;
 int Move::toMask = 0x3F;
 int Move::notNoteMask = ~(0x7000);
 int Move::notPieceTaken = ~(0x7FF << 16);

}
#endif /* MOVE_H_ */
