/*
 * Pawn.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef PAWN_H_
#define PAWN_H_
#include "stdafx.h"
using namespace std;
namespace OhWordC {
class Pawn {
public:
	Pawn();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static vector<long> generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves);
	static void getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo);
	virtual ~Pawn();
};
}
#endif /* PAWN_H_ */
