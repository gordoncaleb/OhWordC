/*
 * RNGTable.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef RNGTABLE_H_
#define RNGTABLE_H_

namespace OhWordC {
class RNGTable {

private:
	static int seed [8];
	static RNGTable* singleton;
	SecureRandom * rng;
	__int64 piecePerSquare [2][6][8][8];
	__int64 blackToMove;
	__int64 castlingRights [2][2][2][2];
	__int64 enPassantFile [8];


public:
	RNGTable();
	static RNGTable * getSingleton();
	__int64 randomLong();
	void generatePiecePerSquare();
	__int64 getPiecePerSquareRandom(side_t player, PieceID id, int row, int col);
	void generateBlackToMove();
	__int64 getBlackToMoveRandom();
	void generateCastlingRights();
	__int64 getCastlingRightsRandom(bool blackFarRook, bool blackNearRook, bool blackKing, bool whiteFarRook, bool whiteNearRook, bool whiteKing);
	void generateEnPassantFile();
	__int64 getEnPassantFile(int file);
	virtual ~RNGTable();
};

}
#endif /* RNGTABLE_H_ */
