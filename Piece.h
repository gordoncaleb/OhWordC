/*
 * Piece.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef PIECE_H_
#define PIECE_H_

using namespace std;

namespace OhWordC {

enum PieceID {
	EMPTY=-1, ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
};

class Board;

class Piece {
	int row;
	int col;
	side_t player;
	bool moved;
	__int64 blockingVector;
	PieceID id;

public:
	Piece();
	Piece(PieceID, side_t, int, int, bool);
	int getRow();
	int getCol();
	virtual ~Piece();
	unsigned __int64 getBit();
	void setPos(int row, int col);
	void move(__int64 newMove);
	void reverseMove(__int64 newMove);
	side_t getSide();
	bool hasMoved();
	void setMoved(bool moved);
	void setBlockingVector(__int64 blockingVector);
	void clearBlocking();
	__int64 getBlockingVector();
	string toString();
	string toXML();
	static PieceID charIDtoPieceID(char type);
	bool equals(Piece * piece);
	bool isValidMove(int, int, __int64[]);
	char getCharID();
	PieceID getPieceID();
	void setPieceID(PieceID id);
	void generateValidMoves(Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves);
	void getNullMoveInfo(Board*, __int64*, __int64, __int64, __int64, __int64, __int64, __int64);
	void getNullMoveInfo(Board*, __int64*);
	Piece * getCopy();
};
}
#endif /* PIECE_H_ */
