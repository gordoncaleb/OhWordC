/*
 * Side.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef SIDE_H_
#define SIDE_H_

namespace OhWordC {

enum side_t {
	BLACK = 0, WHITE = 1, NOONE = 2, BOTH = 4
};

class Side {
public:
	Side();
	static side_t otherSide(side_t side);
	virtual ~Side();
};
}
#endif /* SIDE_H_ */
