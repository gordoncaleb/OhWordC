/*
 * BitBoard.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_

using namespace std;
namespace OhWordC {
class BitBoard {
public:
	BitBoard();
	static unsigned long getCastleMask(int col1, int col2, side_t side);
	static unsigned long getMask(int row, int col);
	static unsigned long getMaskSafe(int row, int col);
	static unsigned long rotateLeft(long bb, int r);
	static unsigned long getColMask(int col);
	static unsigned long getRowMask(int row);
	static unsigned long getBottomRows(int r);
	static unsigned long getNegSlope(int row, int col);
	static unsigned long getPosSlope(int row, int col);
	static unsigned long getTopRows(int r);
	static int getBackedPawns(unsigned long pawns);
	static unsigned long getPawnAttacks(unsigned long pawns, side_t side);
	static unsigned long getKingFootPrint(int row, int col);
	static unsigned long getKingAttacks(unsigned long king);
	static unsigned long getKnightFootPrint(int row, int col);
	static unsigned long getKnightAttacks(unsigned long knights);
	static string printBitBoard(long bitBoard);
	static unsigned long count_bits(long n);
	virtual ~BitBoard();
};
}

#endif /* BITBOARD_H_ */
