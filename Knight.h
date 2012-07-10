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
	static vector<long> generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) ;
	static void getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo);
	virtual ~Knight();
};

int Knight::KNIGHTMOVES [2][8] = { { 2, 2, -2, -2, 1, -1, 1, -1 }, { 1, -1, 1, -1, 2, 2, -2, -2 } };
}
#endif /* KNIGHT_H_ */
