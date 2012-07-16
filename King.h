/*
 * King.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef KING_H_
#define KING_H_

using namespace std;
namespace OhWordC {
class King {

public:
	static int KINGMOVES[2][8];

	King();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece* p, Board* board, vector<__int64>* moves);
	static vector<__int64>* generateValidMoves(Piece* p, Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves);
	static void getNullMoveInfo(Piece* p, Board* board, __int64* nullMoveInfo);
	static __int64 getKingCheckVectors(__int64 king, __int64 updown, __int64 left, __int64 right);
	static bool isValidMove(int toRow, int toCol, __int64* nullMoveInfo);
	static bool canCastleFar(Piece* king, Board* board, side_t player, __int64* nullMoveInfo, __int64 allPosBitBoard);
	static bool canCastleNear(Piece* king, Board* board, side_t player, __int64* nullMoveInfo, __int64 allPosBitBoard);
	virtual ~King();
};

}

#endif /* KING_H_ */
