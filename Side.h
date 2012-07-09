/*
 * Side.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef SIDE_H_
#define SIDE_H_
#include "stdafx.h"

namespace OhWordC {

class Side {
public:
	Side();
	static side_t otherSide(side_t side);
	virtual ~Side();
};
}
#endif /* SIDE_H_ */
