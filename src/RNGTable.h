/*
 * RNGTable.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef RNGTABLE_H_
#define RNGTABLE_H_

class RNGTable {
	static int* seed = {-52, 45, -101, 26, -51, -99, -84, -79};
	Random rng;
	long**** piecePerSquare;
	long blackToMove;
	long**** castlingRights;
	long* enPassantFile;

	static RNGTable singleton;
public:
	RNGTable();
	static RNGTable getSingleton();
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

#endif /* RNGTABLE_H_ */
