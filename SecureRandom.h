/*
 * SecureRandom.h
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#ifndef SECURERANDOM_H_
#define SECURERANDOM_H_
#include "stdafx.h"
namespace OhWordC {

class SecureRandom {
public:
	SecureRandom(int*);
	long nextLong();
	virtual ~SecureRandom();
};

} /* namespace OhWordC */
#endif /* SECURERANDOM_H_ */
