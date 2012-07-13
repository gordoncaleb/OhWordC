/*
 * Values.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef VALUES_H_
#define VALUES_H_

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
}
#endif /* VALUES_H_ */
