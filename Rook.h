/*
 * Rook.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef ROOK_H_
#define ROOK_H_

using namespace std;
namespace OhWordC {
class Rook {

public:
	static int ROOKMOVES [2][4];

	Rook();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece* p, Board* board, vector<long> moves);
	static vector<long> generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves);
	static void getNullMoveInfo(Piece* piece, Board* board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors,long friendly);
	static void getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo);
	virtual ~Rook();
};

int Rook::ROOKMOVES[2][4] = { { 1, -1, 0, 0 }, { 0, 0, 1, -1 } };
}
#endif /* ROOK_H_ */
