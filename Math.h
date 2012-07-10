/*
 * Math.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef MATH_H_
#define MATH_H_

namespace OhWordC {
class Math {
public:
	Math();
	static double pow(double base, double power);
	static int max(int a, int b);
	static int min(int a, int b);
	static double random();
	virtual ~Math();
};



}
#endif /* MATH_H_ */
