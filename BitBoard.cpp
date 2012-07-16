/*
 * BitBoard.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {
BitBoard::BitBoard() {

}

__int64 BitBoard::getCastleMask(int col1, int col2, side_t side) {
	int lowCol;
	int highCol;

	if (col1 >= col2) {
		lowCol = col2;
		highCol = col1;
	} else {
		lowCol = col1;
		highCol = col2;
	}

	if (side == BLACK) {
		return ((0xFFULL >> (7 - highCol + lowCol)) << (lowCol));
	} else {
		return ((0xFFULL >> (7 - highCol + lowCol)) << (lowCol + 56));
	}
}

__int64 BitBoard::getMask(int row, int col) {
	__int64 one = 1;
	return (one << ((row << 3) + col));
}

__int64 BitBoard::getMaskSafe(int row, int col) {
	if (((row | col) & ~7) == 0) {
		return (1ULL << ((row << 3) + col));
	} else {
		return 0;
	}

}

__int64 BitBoard::rotateLeft(unsigned __int64 bb, int r) {
	return ((bb << r) | (bb >> (-r)));
}

__int64 BitBoard::getColMask(int col) {
	return (0x0101010101010101ULL << col);
}

__int64 BitBoard::getRowMask(int row) {
	return (0xFFULL << (row * 8));
}

__int64 BitBoard::getBottomRows(int r) {
	return (0xFF00000000000000ULL >> (r << 3));
}

__int64 BitBoard::getNegSlope(int row, int col) {
	int s = row - col;
	if (s >= 0) {
		return ((0x8040201008040201ULL) << (s << 3));
	} else {
		return ((0x8040201008040201ULL) >> (-s << 3));
	}
}

__int64 BitBoard::getPosSlope(int row, int col) {
	int s = col + row - 7;
	if (s >= 0) {
		return ((0x0102040810204080ULL) << (s << 3));
	} else {
		return ((0x0102040810204080ULL) >> (-s << 3));
	}
}

__int64 BitBoard::getTopRows(int r) {
	return (0xFFFFFFFFFFFFFFFFULL >> ((7 - r) * 8));
}

int BitBoard::getBackedPawns(__int64 pawns) {

	return count_bits(((pawns & 0x7F7F7F7F7F7F7F7FULL) << 7) & pawns) + count_bits(((pawns & 0xFEFEFEFEFEFEFEFEULL) << 9));
}

int BitBoard::count_bits(__int64 n) {
	unsigned int c; // c accumulates the total bits set in v
	for (c = 0; n; c++)
		n &= n - 1; // clear the least significant bit set
	return c;
}

__int64 BitBoard::getPawnAttacks(unsigned __int64 pawns, side_t side) {
	if (side == BLACK) {
		return ((pawns & 0x7F7F7F7F7F7F7F7FULL) << 9) | ((pawns & 0xFEFEFEFEFEFEFEFEULL) << 7);
	} else {
		return ((pawns & 0x7F7F7F7F7F7F7F7FULL) >> 7) | ((pawns & 0xFEFEFEFEFEFEFEFEULL) >> 9);
	}
}

__int64 BitBoard::getKingFootPrint(int row, int col) {

	int shift = ((row - 1) * 8 + col - 1);

	if (shift >= 0) {
		return (0x70507ULL << shift) & (~getColMask(col ^ 7) | (0x7E7E7E7E7E7E7E7EULL));
	} else {
		return (0x70507ULL >> -shift) & (~getColMask(col ^ 7) | (0x7E7E7E7E7E7E7E7EULL));
	}

}

__int64 BitBoard::getKingAttacks(unsigned __int64 king) {
	return (king << 8) | // down 1
			(king >> 8) | // up 1
			((king & 0xFEFEFEFEFEFEFEFEULL) >> 1) | // left 1
			((king & 0x7F7F7F7F7F7F7F7FULL) << 1) | // right 1
			((king & 0x7F7F7F7F7F7F7F7FULL) >> 7) | // up 1 right 1
			((king & 0x7F7F7F7F7F7F7F7FULL) << 9) | // down 1 right 1
			((king & 0xFEFEFEFEFEFEFEFEULL) >> 9) | // up 1 left 1
			((king & 0xFEFEFEFEFEFEFEFEULL) << 7); // down 1 left 1
}

__int64 BitBoard::getKnightFootPrint(int row, int col) {
	int shift = (((row - 2) * 8) + col - 2);

	if (shift >= 0) {
		return (0x0A1100110AULL << shift) & (~(0xC0C0C0C0C0C0C0C0ULL >> (col & 6)) | (0x3c3c3c3c3c3c3c3cULL));
	} else {
		return (0x0A1100110AULL >> -shift) & (~(0xC0C0C0C0C0C0C0C0ULL >> (col & 6)) | (0x3c3c3c3c3c3c3c3cULL));
	}
}

__int64 BitBoard::getKnightAttacks(unsigned __int64 knights) {
	return ((knights & 0xFCFCFCFCFCFCFCFCULL) << 6) | ((knights & 0xFCFCFCFCFCFCFCFCULL) >> 10) | ((knights & 0xFEFEFEFEFEFEFEFEULL) << 15)

	| ((knights & 0xFEFEFEFEFEFEFEFEULL) >> 17) | ((knights & 0x3F3F3F3F3F3F3F3FULL) >> 6) | ((knights & 0x3F3F3F3F3F3F3F3FULL) << 10)
			| ((knights & 0x7F7F7F7F7F7F7F7FULL) >> 15) | ((knights & 0x7F7F7F7F7F7F7F7FULL) << 17);
}

string BitBoard::printBitBoard(__int64 bitBoard) {
	string bitBoardString = "";

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if ((bitBoard & getMask(r, c)) != 0) {
				bitBoardString += "1,";
			} else {
				bitBoardString += "0,";
			}
		}
		bitBoardString += "\n";
	}

// System.out.println(bitBoardString);

	return bitBoardString;
}

BitBoard::~BitBoard() {

}

}

