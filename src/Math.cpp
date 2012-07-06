/*
 * Math.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Math.h"

Math::Math() {
	// TODO Auto-generated constructor stub

}

static double Math::pow(double base, double power) {
	double out = 1;
	while (power > 0) {
		out *= base;
		power--;
	}
	return out;
}

static int Math::max(int a, int b) {
	return (a >= b) ? a : b;
}

static int Math::min(int a, int b) {
	return (a < b) ? a : b;
}

Math::~Math() {
// TODO Auto-generated destructor stub
}

