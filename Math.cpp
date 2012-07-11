/*
 * Math.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"

namespace OhWordC {
Math::Math() {
	// TODO Auto-generated constructor stub

}

double pow(double base, double power) {
	double out = 1;
	while (power > 0) {
		out *= base;
		power--;
	}
	return out;
}

int max(int a, int b) {
	return (a >= b) ? a : b;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

double random() {
	return ((double) rand() / (double) RAND_MAX);
}

Math::~Math() {
// TODO Auto-generated destructor stub
}

}

