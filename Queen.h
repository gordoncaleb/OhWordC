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
	static void generateMoves(Piece* p, Board* board, vector<long> moves);
	static vector<long> generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves);
	static void getNullMoveInfo(Piece* piece, Board* board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors,long friendly);
	static void getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo);
	virtual ~Queen();
};

int Queen::QUEENMOVES [2][8]= { { 1, 1, -1, -1, 1, -1, 0, 0 }, { 1, -1, 1, -1, 0, 0, 1, -1 } };
}
#endif /* QUEEN_H_ */
