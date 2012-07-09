/*
 * PositionBonus.h
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#ifndef POSITIONBONUS_H_
#define POSITIONBONUS_H_
#include "stdafx.h"
using namespace std;

namespace OhWordC {

class PositionBonus {
	static int knightBonus[8][8];
	static int kingOpeningBonus[8][8];
	static int kingEndGameBonus[8][8];
	static int rookBonus[8][8];
	static int pawnBonus[8][8];
public:
	PositionBonus();
	static void applyScale();
	static void printBonus(int** bonus, string name);
	static void scalePositionBonus(int** bonus, double scale);
	static int getKnightMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player);
	static int getKnightPositionBonus(int row, int col, side_t player);
	static int getKingOpeningPositionBonus(int row, int col, side_t player);
	static int getKingEndGamePositionBonus(int row, int col, side_t player);
	static int getRookBonus(int row, int col);
	static int getPawnMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player);
	static int getPawnPositionBonus(int row, int col, side_t player);
	virtual ~PositionBonus();
};

int knightBonus[8][8] = { { -30, -20, -10, -10, -10, -10, -20, -30 }, // 1
		{ -20, 10, 10, 10, 10, 10, 10, -20 }, // 2
		{ -10, 10, 20, 20, 20, 20, 10, -10 }, // 3
		{ -10, 10, 20, 25, 25, 20, 10, -10 }, // 4
		{ -10, 10, 20, 25, 25, 20, 10, -10 }, // 5
		{ -10, 10, 20, 20, 20, 20, 10, -10 }, // 6
		{ -20, 10, 10, 10, 10, 10, 10, -20 }, // 7
		{ -30, -20, -10, -10, -10, -10, -20, -30 } // 8
// a, b, c, d, e, f, g, h
};

int kingOpeningBonus[8][8] = { { 25, 25, 35, 0, 10, 0, 40, 35 }, // 1
		{ 10, 10, 5, 0, 0, 5, 10, 15 }, // 2
		{ 5, 0, -10, -10, -10, -10, 0, 5 }, // 3
		{ 0, -15, -20, -25, -25, -20, -15, 0 }, // 4
		{ -20, -25, -30, -35, -35, -30, -25, -20 }, // 5
		{ -30, -35, -40, -45, -45, -40, -35, -30 }, // 6
		{ -40, -40, -50, -55, -55, -50, -45, -40 }, // 7
		{ -50, -45, -60, -65, -65, -60, -55, -50 } // 8
// a, b, c, d, e, f, g, h
};

int kingEndGameBonus[8][8] = { { -10, -5, 0, 0, 0, 0, -5, -10 }, // 1
		{ -5, 20, 20, 20, 20, 20, 20, -5 }, // 2
		{ 0, 20, 40, 40, 40, 40, 20, 0 }, // 3
		{ 0, 20, 40, 45, 45, 40, 20, 0 }, // 4
		{ 0, 20, 40, 45, 45, 40, 20, 0 }, // 5
		{ 0, 20, 40, 40, 40, 40, 20, 0 }, // 6
		{ -5, 20, 20, 20, 20, 20, 20, -5 }, // 7
		{ -10, -5, 0, 0, 0, 0, -5, -10 } // 8
// a, b, c, d, e, f, g, h
};

int rookBonus[8][8] = { { 0, 0, 7, 10, 10, 5, 0, 0 }, // 1
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 2
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 3
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 4
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 5
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 6
		{ -5, 5, 10, 10, 10, 10, 5, -5 }, // 7
		{ 0, 0, 0, 0, 0, 0, 0, 0 } // 8
// a, b, c, d, e, f, g, h
};

int pawnBonus[8][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, // 1
		{ 5, 2, 2, -10, -10, 2, 2, 5 }, // 2
		{ 5, 0, 0, 0, 0, 0, 0, 5 }, // 3
		{ 0, 10, 10, 15, 15, 10, 10, 0 }, // 4
		{ 10, 15, 15, 20, 20, 15, 15, 10 }, // 5
		{ 20, 20, 20, 20, 20, 20, 20, 20 }, // 6
		{ 40, 40, 40, 40, 40, 40, 40, 40 }, // 7
		{ 0, 0, 0, 0, 0, 0, 0, 0 } // 8
// a, b, c, d, e, f, g, h
};

} /* namespace OhWordC */
#endif /* POSITIONBONUS_H_ */
