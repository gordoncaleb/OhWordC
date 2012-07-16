/*
 * Move.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef MOVE_H_
#define MOVE_H_

using namespace std;
namespace OhWordC {
enum MoveNote {
	NONE, CASTLE_NEAR, CASTLE_FAR, NEW_QUEEN, ENPASSANT, PAWN_LEAP
};

class Move {

	static int hadMovedMask;
	static int hasPieceTakenMask;
	static int pieceTakenHasMoved;
	static int fromToMask;
	static int fromMask;
	static int toMask;
	static int notNoteMask;
	static int notPieceTaken;

	__int64 move;

public:
	Move(__int64 moveInt);
	Move(int fromRow, int fromCol, int toRow, int toCol);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken);
	Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved);
	void setMoveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece* pieceTaken, bool hadMoved);

	static __int64 moveLong(int fromRow, int fromCol, int toRow, int toCol);
	static __int64 moveLong(int fromRow, int fromCol, int toRow, int toCol, int value);
	static __int64 moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note);
	static __int64 moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece* pieceTaken);
	static __int64 moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece* pieceTaken, bool hadMoved);

	bool equals(Move move);
	static bool equals(__int64 moveLongA, __int64 moveLongB);
	static bool fromEquals(__int64 moveLongA, __int64 moveLongB);
	static bool toEquals(__int64 moveLongA, __int64 moveLongB);
	//string toXML();
	//static string toXML(__int64 moveLong);
	__int64 setNote(MoveNote note);
	static __int64 setNote(__int64 moveLong, MoveNote note);
	MoveNote getNote();
	static MoveNote getNote(__int64 moveLong);
	int getFromRow();
	static int getFromRow(__int64 moveLong);
	int getFromCol();
	static int getFromCol(__int64 moveLong);
	int getToRow();
	static int getToRow(__int64 moveLong);
	int getToCol();
	static int getToCol(__int64 moveLong);
	int getValue();
	static int getValue(__int64 moveLong);
	__int64 setValue(int value);
	static __int64 setValue(__int64 moveLong, int value);
	__int64 setPieceTaken(Piece* pieceTaken);
	static __int64 setPieceTaken(__int64 moveLong, Piece* pieceTaken);
	bool hadMoved();
	static bool hadMoved(__int64 moveLong);
	__int64 setHadMoved(bool hadMoved);
	static __int64 setHadMoved(__int64 moveLong, bool hadMoved);
	bool hasPieceTaken();
	static bool hasPieceTaken(__int64 moveLong);
	bool getPieceTakenHasMoved();
	static bool getPieceTakenHasMoved(__int64 moveLong);
	int getPieceTakenRow();
	static int getPieceTakenRow(__int64 moveLong);
	int getPieceTakenCol();
	static int getPieceTakenCol(__int64 moveLong);
	PieceID getPieceTakenID();
	static PieceID getPieceTakenID(__int64 moveLong);
	Move * getCopy();
	__int64 getMoveLong();

	virtual ~Move();
};

}
#endif /* MOVE_H_ */
