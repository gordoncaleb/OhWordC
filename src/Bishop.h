/*
 * Bishop.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef BISHOP_H_
#define BISHOP_H_

using namespace std;

class Bishop {

	static int** BISHOPMOVES = { { 1, 1, -1, -1 }, { 1, -1, 1, -1 } };

public:
	Bishop();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece p, Board board, vector<long> moves);
	static vector<long> generateValidMoves(Piece p, Board board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves);
	static void getNullMoveInfo(Piece piece, Board board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors,
			long friendly);
	static void getNullMoveInfo(Piece p, Board board, long* nullMoveInfo);
	virtual ~Bishop();
};

#endif /* BISHOP_H_ */
