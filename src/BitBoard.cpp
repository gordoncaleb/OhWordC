/*
 * BitBoard.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "BitBoard.h"

BitBoard::BitBoard() {

}

static unsigned long BitBoard::getCastleMask(int col1, int col2, side_t side) {
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
		return ((0xFFL >> (7 - highCol + lowCol)) << (lowCol));
	} else {
		return ((0xFFL >> (7 - highCol + lowCol)) << (lowCol + 56));
	}
}

static unsigned long BitBoard::getMask(int row, int col) {
	return (1L << ((row << 3) + col));
}

static unsigned long BitBoard::getMaskSafe(int row, int col) {
	if (((row | col) & ~7) == 0) {
		return (1L << ((row << 3) + col));
	} else {
		return 0;
	}

}

static unsigned long BitBoard::rotateLeft(long bb, int r) {
	return ((bb << r) | (bb >> (-r)));
}

static unsigned long BitBoard::getColMask(int col) {
	return (0x0101010101010101L << col);
}

static unsigned long BitBoard::getRowMask(int row) {
	return (0xFFUL << (row * 8));
}

static unsigned long BitBoard::getBottomRows(int r) {
	return (0xFF00000000000000L >> (r << 3));
}

static unsigned long BitBoard::getNegSlope(int row, int col) {
	int s = row - col;
	if (s >= 0) {
		return ((0x8040201008040201UL) << (s << 3));
	} else {
		return ((0x8040201008040201UL) >> (-s << 3));
	}
}

static unsigned long BitBoard::getPosSlope(int row, int col) {
	int s = col + row - 7;
	if (s >= 0) {
		return ((0x0102040810204080UL) << (s << 3));
	} else {
		return ((0x0102040810204080UL) >> (-s << 3));
	}
}

static unsigned long BitBoard::getTopRows(int r) {
	return (0xFFFFFFFFFFFFFFFFUL >> ((7 - r) * 8));
}

static int BitBoard::getBackedPawns(unsigned long pawns) {

	return count_bits(((pawns & 0x7F7F7F7F7F7F7F7FUL) << 7) & pawns) + count_bits(((pawns & 0xFEFEFEFEFEFEFEFEUL) << 9));
}

static unsigned long BitBoard::count_bits(long n) {
	unsigned int c; // c accumulates the total bits set in v
	for (c = 0; n; c++)
		n &= n - 1; // clear the least significant bit set
	return c;
}

static unsigned long BitBoard::getPawnAttacks(unsigned long pawns, side_t side) {
	if (side == BLACK) {
		return ((pawns & 0x7F7F7F7F7F7F7F7FUL) << 9) | ((pawns & 0xFEFEFEFEFEFEFEFEUL) << 7);
	} else {
		return ((pawns & 0x7F7F7F7F7F7F7F7FUL) >> 7) | ((pawns & 0xFEFEFEFEFEFEFEFEUL) >> 9);
	}
}

static unsigned long BitBoard::getKingFootPrint(int row, int col) {

	int shift = ((row - 1) * 8 + col - 1);

	if (shift >= 0) {
		return (0x70507UL << shift) & (~getColMask(col ^ 7) | (0x7E7E7E7E7E7E7E7EUL));
	} else {
		return (0x70507UL >> -shift) & (~getColMask(col ^ 7) | (0x7E7E7E7E7E7E7E7EUL));
	}

}

static unsigned long BitBoard::getKingAttacks(unsigned long king) {
	return (king << 8) | // down 1
			(king >> 8) | // up 1
			((king & 0xFEFEFEFEFEFEFEFEUL) >> 1) | // left 1
			((king & 0x7F7F7F7F7F7F7F7FUL) << 1) | // right 1
			((king & 0x7F7F7F7F7F7F7F7FUL) >> 7) | // up 1 right 1
			((king & 0x7F7F7F7F7F7F7F7FUL) << 9) | // down 1 right 1
			((king & 0xFEFEFEFEFEFEFEFEUL) >> 9) | // up 1 left 1
			((king & 0xFEFEFEFEFEFEFEFEUL) << 7); // down 1 left 1
}

static unsigned long BitBoard::getKnightFootPrint(int row, int col) {
	int shift = (((row - 2) * 8) + col - 2);

	if (shift >= 0) {
		return (0x0A1100110AUL << shift) & (~(0xC0C0C0C0C0C0C0C0UL >> (col & 6)) | (0x3c3c3c3c3c3c3c3cUL));
	} else {
		return (0x0A1100110AUL >> -shift) & (~(0xC0C0C0C0C0C0C0C0UL >> (col & 6)) | (0x3c3c3c3c3c3c3c3cUL));
	}
}

static unsigned long BitBoard::getKnightAttacks(unsigned long knights) {
	return ((knights & 0xFCFCFCFCFCFCFCFCUL) << 6) | ((knights & 0xFCFCFCFCFCFCFCFCUL) >> 10) | ((knights & 0xFEFEFEFEFEFEFEFEUL) << 15)

	| ((knights & 0xFEFEFEFEFEFEFEFEUL) >> 17) | ((knights & 0x3F3F3F3F3F3F3F3FUL) >> 6) | ((knights & 0x3F3F3F3F3F3F3F3FUL) << 10)
			| ((knights & 0x7F7F7F7F7F7F7F7FUL) >> 15) | ((knights & 0x7F7F7F7F7F7F7F7FUL) << 17);
}

static string BitBoard::printBitBoard(long bitBoard) {
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

