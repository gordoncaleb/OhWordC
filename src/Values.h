/*
 * Values.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef VALUES_H_
#define VALUES_H_

class Values {

	static int CHECKMATE_MASK = (int) Math::pow(2, 19);

	static int KING_VALUE = (int) Math::pow(2, 20) - 1;
	static int QUEEN_VALUE = 1200;
	static int ROOK_VALUE = 600;
	static int BISHOP_VALUE = 400;
	static int KNIGHT_VALUE = 390;
	static int PAWN_VALUE = 100;
	static int NEAR_CASTLE_VALUE = 90;
	static int FAR_CASTLE_VALUE = 80;
	static int NEAR_CASTLE_ABILITY_LOST_VALUE = 50;
	static int FAR_CASTLE_ABILITY_LOST_VALUE = 40;
	static int CASTLE_ABILITY_LOST_VALUE = FAR_CASTLE_ABILITY_LOST_VALUE + NEAR_CASTLE_ABILITY_LOST_VALUE;
	static int CHECKMATE_MOVE = KING_VALUE;

	static int BACKED_PAWN_BONUS = 2;
	static int DOUBLED_PAWN_BONUS = -5;
	static int PASSED_PAWN_BONUS = 10;

	static int PAWNPHASE = 0;
	static int KNIGHTPHASE = 1;
	static int BISHOPPHASE = 1;
	static int ROOKPHASE = 2;
	static int QUEENPHASE = 4;

	static int TOTALPHASE = PAWNPHASE * 16 + KNIGHTPHASE * 4 + BISHOPPHASE * 4 + ROOKPHASE * 4 + QUEENPHASE * 2;
	static int** PIECE_PHASE_VAL = {ROOKPHASE, KNIGHTPHASE, BISHOPPHASE, QUEENPHASE, 0, PAWNPHASE};
	static int* PIECE_VALUE = {ROOK_VALUE,KNIGHT_VALUE,BISHOP_VALUE,QUEEN_VALUE,KING_VALUE,PAWN_VALUE};

public:
	Values();
	static int getPieceValue(PieceID id);
	virtual ~Values();
};

#endif /* VALUES_H_ */
