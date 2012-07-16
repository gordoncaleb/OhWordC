/*
 * Pawn.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef PAWN_H_
#define PAWN_H_

using namespace std;
namespace OhWordC {
class Pawn {
public:
	Pawn();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static vector<__int64>* generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves);
	static void getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo);
	virtual ~Pawn();
};
}
#endif /* PAWN_H_ */
