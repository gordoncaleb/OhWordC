/*
 * Piece.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef PIECE_H_
#define PIECE_H_

using namespace std;

enum PieceID {
	ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
};

class Piece {
	int row;
	int col;
	side_t player;
	bool moved;
	long blockingVector;
	PieceID id;

public:
	Piece(PieceID, side_t, int, int, bool);
	int getRow();
	int getCol();
	virtual ~Piece();
	unsigned long getBit();
	void setPos(int row, int col);
	void move(long newMove);
	void reverseMove(long newMove);
	side_t getSide();
	bool hasMoved();
	void setMoved(bool moved);
	void setBlockingVector(long blockingVector);
	void clearBlocking();
	long getBlockingVector();
	static Piece fromString(string stringPiece, int row, int col);
	static PieceID charIDtoPieceID(char type);
	bool equals(Piece piece);
	bool isValidMove(int, int, long[]);
	PieceID getPieceID();
	void setPieceID(PieceID id);
	void generateValidMoves(Board, long[], long[], vector<long>);
	void getNullMoveInfo(Board, long[], long, long, long, long, long, long);
	void getNullMoveInfo(Board, long[]);
	Piece getCopy();
};

#endif /* PIECE_H_ */
