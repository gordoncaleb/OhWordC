/*
 * Side.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Side.h"
namespace OhWordC {
Side::Side() {
	// TODO Auto-generated constructor stub

}

static side_t Side::otherSide(side_t side) {
	return side ^ 3;
}

Side::~Side() {
// TODO Auto-generated destructor stub
}
}
