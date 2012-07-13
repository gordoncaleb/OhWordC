/*
 * PositionBonus.h
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#ifndef POSITIONBONUS_H_
#define POSITIONBONUS_H_

using namespace std;

namespace OhWordC {

class PositionBonus {
public:
	static int knightBonus[8][8];
	static int kingOpeningBonus[8][8];
	static int kingEndGameBonus[8][8];
	static int rookBonus[8][8];
	static int pawnBonus[8][8];

	PositionBonus();
	static void applyScale();
	static void printBonus(int bonus[8][8], string name);
	static void scalePositionBonus(int bonus[8][8], double scale);
	static int getKnightMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player);
	static int getKnightPositionBonus(int row, int col, side_t player);
	static int getKingOpeningPositionBonus(int row, int col, side_t player);
	static int getKingEndGamePositionBonus(int row, int col, side_t player);
	static int getRookBonus(int row, int col);
	static int getPawnMoveBonus(int fromRow, int fromCol, int toRow, int toCol, side_t player);
	static int getPawnPositionBonus(int row, int col, side_t player);
	virtual ~PositionBonus();
};

} /* namespace OhWordC */
#endif /* POSITIONBONUS_H_ */
