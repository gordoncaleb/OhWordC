/*
 * Values.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {
Values::Values() {
	// TODO Auto-generated constructor stub

}

int getPieceValue(PieceID id){
	return Values::PIECE_VALUE[id];
}

Values::~Values() {
	// TODO Auto-generated destructor stub
}
}
