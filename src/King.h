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
	static int** KINGMOVES = { { 1, 1, -1, -1, 1, -1, 0, 0 }, { 1, -1, 1, -1, 0, 0, 1, -1 } };
public:
	King();
	static PieceID getPieceID();
	static string getName();
	static string getStringID();
	static void generateMoves(Piece* p, Board* board, vector<long> moves);
	static vector<long> generateValidMoves(Piece* p, Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves);
	static void getNullMoveInfo(Piece* p, Board* board, long* nullMoveInfo);
	static long getKingCheckVectors(long king, long updown, long left, long right);
	static bool isValidMove(int toRow, int toCol, long* nullMoveInfo);
	static bool canCastleFar(Piece* king, Board* board, side_t player, long* nullMoveInfo, long allPosBitBoard);
	static bool canCastleNear(Piece* king, Board* board, side_t player, long* nullMoveInfo, long allPosBitBoard);
	virtual ~King();
};
}

#endif /* KING_H_ */
