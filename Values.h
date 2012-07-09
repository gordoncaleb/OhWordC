/*
 * Values.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef VALUES_H_
#define VALUES_H_
#include "stdafx.h"
namespace OhWordC {

class Values {
public:
	static int CHECKMATE_MASK;

	static int KING_VALUE;
	static int QUEEN_VALUE;
	static int ROOK_VALUE;
	static int BISHOP_VALUE;
	static int KNIGHT_VALUE;
	static int PAWN_VALUE;
	static int NEAR_CASTLE_VALUE;
	static int FAR_CASTLE_VALUE;
	static int NEAR_CASTLE_ABILITY_LOST_VALUE;
	static int FAR_CASTLE_ABILITY_LOST_VALUE;
	static int CASTLE_ABILITY_LOST_VALUE;
	static int CHECKMATE_MOVE;

	static int BACKED_PAWN_BONUS;
	static int DOUBLED_PAWN_BONUS;
	static int PASSED_PAWN_BONUS;

	static int PAWNPHASE;
	static int KNIGHTPHASE;
	static int BISHOPPHASE;
	static int ROOKPHASE;
	static int QUEENPHASE;

	static int TOTALPHASE;
	static int PIECE_PHASE_VAL [6];
	static int PIECE_VALUE [6];

	Values();
	static int getPieceValue(PieceID id);
	virtual ~Values();
};

int Values::CHECKMATE_MASK = (int) Math::pow(2, 19);

int Values::KING_VALUE = (int) Math::pow(2, 20) - 1;
int Values::QUEEN_VALUE = 1200;
int Values::ROOK_VALUE = 600;
int Values::BISHOP_VALUE = 400;
int Values::KNIGHT_VALUE = 390;
int Values::PAWN_VALUE = 100;
int Values::NEAR_CASTLE_VALUE = 90;
int Values::FAR_CASTLE_VALUE = 80;
int Values::NEAR_CASTLE_ABILITY_LOST_VALUE = 50;
int Values::FAR_CASTLE_ABILITY_LOST_VALUE = 40;
int Values::CASTLE_ABILITY_LOST_VALUE = FAR_CASTLE_ABILITY_LOST_VALUE + NEAR_CASTLE_ABILITY_LOST_VALUE;
int Values::CHECKMATE_MOVE = KING_VALUE;

int Values::BACKED_PAWN_BONUS = 2;
int Values::DOUBLED_PAWN_BONUS = -5;
int Values::PASSED_PAWN_BONUS = 10;

int Values::PAWNPHASE = 0;
int Values::KNIGHTPHASE = 1;
int Values::BISHOPPHASE = 1;
int Values::ROOKPHASE = 2;
int Values::QUEENPHASE = 4;

int Values::TOTALPHASE = PAWNPHASE * 16 + KNIGHTPHASE * 4 + BISHOPPHASE * 4 + ROOKPHASE * 4 + QUEENPHASE * 2;
int Values::PIECE_PHASE_VAL [6] = { ROOKPHASE, KNIGHTPHASE, BISHOPPHASE, QUEENPHASE, 0, PAWNPHASE };
int Values::PIECE_VALUE[6] = { ROOK_VALUE, KNIGHT_VALUE, BISHOP_VALUE, QUEEN_VALUE, KING_VALUE, PAWN_VALUE };
}
#endif /* VALUES_H_ */
