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
	static int seed [8];
	static RNGTable * singleton;
	SecureRandom * rng;
	long piecePerSquare [2][6][8][8];
	long blackToMove;
	long castlingRights [2][2][2][2];
	long enPassantFile [8];


public:
	RNGTable();
	static RNGTable * getSingleton();
	long randomLong();
	void generatePiecePerSquare();
	long getPiecePerSquareRandom(side_t player, PieceID id, int row, int col);
	void generateBlackToMove();
	long getBlackToMoveRandom();
	void generateCastlingRights();
	long getCastlingRightsRandom(bool blackFarRook, bool blackNearRook, bool blackKing, bool whiteFarRook, bool whiteNearRook, bool whiteKing);
	void generateEnPassantFile();
	long getEnPassantFile(int file);
	virtual ~RNGTable();
};

int RNGTable::seed [8] =  {-52, 45, -101, 26, -51, -99, -84, -79};

}
#endif /* RNGTABLE_H_ */
