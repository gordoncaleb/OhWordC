/*
 * Knight.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

namespace OhWordC {
using namespace std;
class Knight {
public:
	static int KNIGHTMOVES [2][8];
	Knight();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static vector<__int64>* generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves) ;
	static void getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo);
	virtual ~Knight();
};

}
#endif /* KNIGHT_H_ */
