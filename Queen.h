/*
 * Queen.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef QUEEN_H_
#define QUEEN_H_

using namespace std;

namespace OhWordC {
class Queen {

public:
	static int QUEENMOVES [2][8];

	Queen();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece* p, Board* board, vector<__int64>* moves);
	static vector<__int64>* generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves);
	static void getNullMoveInfo(Piece* piece, Board* board, __int64* nullMoveInfo, __int64 updown, __int64 left, __int64 right, __int64 kingBitBoard, __int64 kingCheckVectors,__int64 friendly);
	static void getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo);
	virtual ~Queen();
};

}
#endif /* QUEEN_H_ */
