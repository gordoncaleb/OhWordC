/*
 * PositionBonus.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#include "stdafx.h"

namespace OhWordC {

int PositionBonus::knightBonus[8][8] = { { -30, -20, -10, -10, -10, -10, -20, -30 }, // 1
		{ -20, 10, 10, 10, 10, 10, 10, -20 }, // 2
		{ -10, 10, 20, 20, 20, 20, 10, -10 }, // 3
		{ -10, 10, 20, 25, 25, 20, 10, -10 }, // 4
		{ -10, 10, 20, 25, 25, 20, 10, -10 }, // 5
		{ -10, 10, 20, 20, 20, 20, 10, -10 }, // 6
		{ -20, 10, 10, 10, 10, 10, 10, -20 }, // 7
		{ -30, -20, -10, -10, -10, -10, -20, -30 } // 8
// a, b, c, d, e, f, g, h
};

int PositionBonus::kingOpeningBonus[8][8] = { { 25, 25, 35, 0, 10, 0, 40, 35 }, // 1
		{ 10, 10, 5, 0, 0, 5, 10, 15 }, // 2
		{ 5, 0, -10, -10, -10, -10, 0, 5 }, // 3
		{ 0, -15, -20, -25, -25, -20, -15, 0 }, // 4
		{ -20, -25, -30, -35, -35, -30, -25, -20 }, // 5
		{ -30, -35, -40, -45, -45, -40, -35, -30 }, // 6
		{ -40, -40, -50, -55, -55, -50, -45, -40 }, // 7
		{ -50, -45, -60, -65, -65, -60, -55, -50 } // 8
// a, b, c, d, e, f, g, h
};

int PositionBonus::kingEndGameBonus[8][8] = { { -10, -5, 0, 0, 0, 0, -5, -10 }, // 1
		{ -5, 20, 20, 20, 20, 20, 20, -5 }, // 2
		{ 0, 20, 40, 40, 40, 40, 20, 0 }, // 3
		{ 0, 20, 40, 45, 45, 40, 20, 0 }, // 4
		{ 0, 20, 40, 45, 45, 40, 20, 0 }, // 5
		{ 0, 20, 40, 40, 40, 40, 20, 0 }, // 6
		{ -5, 20, 20, 20, 20, 20, 20, -5 }, // 7
		{ -10, -5, 0, 0, 0, 0, -5, -10 } // 8
// a, b, c, d, e, f, g, h
};

int PositionBonus::rookBonus[8][8] = { { 0, 0, 7, 10, 10, 5, 0, 0 }, // 1
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 2
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 3
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 4
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 5
		{ -5, 0, 0, 0, 0, 0, 0, -5 }, // 6
		{ -5, 5, 10, 10, 10, 10, 5, -5 }, // 7
		{ 0, 0, 0, 0, 0, 0, 0, 0 } // 8
// a, b, c, d, e, f, g, h
};

int PositionBonus::pawnBonus[8][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 }, // 1
		{ 5, 2, 2, -10, -10, 2, 2, 5 }, // 2
		{ 5, 0, 0, 0, 0, 0, 0, 5 }, // 3
		{ 0, 10, 10, 15, 15, 10, 10, 0 }, // 4
		{ 10, 15, 15, 20, 20, 15, 15, 10 }, // 5
		{ 20, 20, 20, 20, 20, 20, 20, 20 }, // 6
		{ 40, 40, 40, 40, 40, 40, 40, 40 }, // 7
		{ 0, 0, 0, 0, 0, 0, 0, 0 } // 8
// a, b, c, d, e, f, g, h
};

PositionBonus::PositionBonus() {
	// TODO Auto-generated constructor stub

}

void PositionBonus::applyScale() {
	scalePositionBonus(pawnBonus, 0.5);
	scalePositionBonus(rookBonus, 0.5);
	scalePositionBonus(kingEndGameBonus, 0.5);
	scalePositionBonus(kingOpeningBonus, 0.5);
	scalePositionBonus(knightBonus, 0.5);

	printBonus(pawnBonus, "pawn");
	printBonus(rookBonus, "rook");
	printBonus(kingEndGameBonus, "king endgame");
	printBonus(kingOpeningBonus, "king opening");
	printBonus(knightBonus, "knight");
}

void PositionBonus::printBonus(int bonus[8][8], string name) {

	printf("%s + Bonus{", name.c_str());
	for (int i = 0; i < 8; i++) {
		for (int y = 0; y < 8; y++) {
			printf("%3d,", bonus[i][y]);
		}
		printf("\n");
	}

	printf("}");
}

void PositionBonus::scalePositionBonus(int bonus[8][8], double scale) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			bonus[r][c] = (int) (bonus[r][c] * scale);
		}
	}
}

int PositionBonus::getKnightMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = knightBonus[toRow][toCol] - knightBonus[fromRow][fromCol];
	} else {
		bonus = knightBonus[7 - toRow][toCol] - knightBonus[7 - fromRow][fromCol];
	}
	return bonus;
}

int PositionBonus::getKnightPositionBonus(int row, int col, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = knightBonus[row][col];
	} else {
		bonus = knightBonus[7 - row][col];
	}
	return bonus;
}

int PositionBonus::getKingOpeningPositionBonus(int row, int col, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = kingOpeningBonus[row][col];
	} else {
		bonus = kingOpeningBonus[7 - row][col];
	}
	return bonus;
}

int PositionBonus::getKingEndGamePositionBonus(int row, int col, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = kingEndGameBonus[row][col];
	} else {
		bonus = kingEndGameBonus[7 - row][col];
	}
	return bonus;
}

int PositionBonus::getRookBonus(int row, int col) {
	return rookBonus[row][col];
}

int PositionBonus::getPawnMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = pawnBonus[toRow][toCol] - pawnBonus[fromRow][fromCol];
	} else {
		bonus = pawnBonus[7 - toRow][toCol] - pawnBonus[7 - fromRow][fromCol];
	}
	return bonus;
}

int PositionBonus::getPawnPositionBonus(int row, int col, side_t player) {
	int bonus;
	if (player == BLACK) {
		bonus = pawnBonus[row][col];
	} else {
		bonus = pawnBonus[7 - row][col];
	}
	return bonus;
}

PositionBonus::~PositionBonus() {
	// TODO Auto-generated destructor stub
}

} /* namespace OhWordC */
