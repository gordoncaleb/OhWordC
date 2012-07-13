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
	static __int64 getCastleMask(int col1, int col2, side_t side);
	static __int64 getMask(int row, int col);
	static __int64 getMaskSafe(int row, int col);
	static __int64 rotateLeft(unsigned __int64 bb, int r);
	static __int64 getColMask(int col);
	static __int64 getRowMask(int row);
	static __int64 getBottomRows(int r);
	static __int64 getNegSlope(int row, int col);
	static __int64 getPosSlope(int row, int col);
	static __int64 getTopRows(int r);
	static int getBackedPawns(__int64 pawns);
	static __int64 getPawnAttacks(unsigned __int64 pawns, side_t side);
	static __int64 getKingFootPrint(int row, int col);
	static __int64 getKingAttacks(unsigned __int64 king);
	static __int64 getKnightFootPrint(int row, int col);
	static __int64 getKnightAttacks(unsigned __int64 knights);
	static string printBitBoard(__int64 bitBoard);
	static int count_bits(__int64 n);
	virtual ~BitBoard();
};
}

#endif /* BITBOARD_H_ */
