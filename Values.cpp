/*
 * Values.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {

int Values::CHECKMATE_MASK = 524288;
int Values::KING_VALUE = 1048575;
int Values::QUEEN_VALUE = 1200;
int Values::ROOK_VALUE = 600;
int Values::BISHOP_VALUE = 400;
int Values::KNIGHT_VALUE = 390;
int Values::PAWN_VALUE = 100;
int Values::NEAR_CASTLE_VALUE = 90;
int Values::FAR_CASTLE_VALUE = 80;
int Values::NEAR_CASTLE_ABILITY_LOST_VALUE = 50;
int Values::FAR_CASTLE_ABILITY_LOST_VALUE = 40;
int Values::CASTLE_ABILITY_LOST_VALUE = Values::FAR_CASTLE_ABILITY_LOST_VALUE + Values::NEAR_CASTLE_ABILITY_LOST_VALUE;
int Values::CHECKMATE_MOVE = Values::KING_VALUE;

int Values::BACKED_PAWN_BONUS = 2;
int Values::DOUBLED_PAWN_BONUS = -5;
int Values::PASSED_PAWN_BONUS = 10;

int Values::PAWNPHASE = 0;
int Values::KNIGHTPHASE = 1;
int Values::BISHOPPHASE = 1;
int Values::ROOKPHASE = 2;
int Values::QUEENPHASE = 4;

int Values::TOTALPHASE = Values::PAWNPHASE * 16 + Values::KNIGHTPHASE * 4 + Values::BISHOPPHASE * 4 + Values::ROOKPHASE * 4 + Values::QUEENPHASE * 2;
int Values::PIECE_PHASE_VAL [6] = { Values::ROOKPHASE, Values::KNIGHTPHASE, Values::BISHOPPHASE, Values::QUEENPHASE, 0, Values::PAWNPHASE };
int Values::PIECE_VALUE[6] = { Values::ROOK_VALUE, Values::KNIGHT_VALUE, Values::BISHOP_VALUE, Values::QUEEN_VALUE, Values::KING_VALUE, Values::PAWN_VALUE };


Values::Values() {
	// TODO Auto-generated constructor stub

}

int Values::getPieceValue(PieceID id){
	return Values::PIECE_VALUE[id];
}

Values::~Values() {
	// TODO Auto-generated destructor stub
}
}
