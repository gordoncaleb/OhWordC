/*
 * PositionBonus.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#include "stdafx.h"

namespace OhWordC {

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
