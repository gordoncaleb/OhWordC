/*
 * stdafx.h
 *
 *  Created on: Jul 8, 2012
 *      Author: Caleb
 */

#ifndef STDAFX_H_
#define STDAFX_H_

enum side_t {
	BLACK = 1, WHITE = 2, NOONE = 4, BOTH = 8
};

enum PieceID {
	ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
};

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include "Math.h"
#include "Values.h"
#include "Side.h"
#include "Piece.h"
//#include "SecureRandom.h"
//#include "RNGTable.h"
//#include "Move.h"
//#include "Board.h"
//#include "PositionBonus.h"
//
//#include "Pawn.h"
//#include "Bishop.h"
//#include "King.h"
//#include "Knight.h"
//#include "Queen.h"
//#include "BitBoard.h"
//#include "BoardMaker.h"

#endif /* STDAFX_H_ */
