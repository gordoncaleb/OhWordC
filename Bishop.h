/*
 * Bishop.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef BISHOP_H_
#define BISHOP_H_

using namespace std;

namespace OhWordC {
class Bishop {

public:
	static int BISHOPMOVES [2][4];

	Bishop();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece* p, Board* board, vector<__int64> * moves);
	static vector<__int64>* generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64>* validMoves);
	static void getNullMoveInfo(Piece* piece, Board* board, __int64* nullMoveInfo, __int64 updown, __int64 left, __int64 right, __int64 kingBitBoard, __int64 kingCheckVectors,
			__int64 friendly);
	static void getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo);
	virtual ~Bishop();
};

}

#endif /* BISHOP_H_ */
