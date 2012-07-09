/*
 ============================================================================
 Name        : OhWordC.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <stdio.h>

#include "Math.h"

using namespace std;
using namespace OhWordC;

int main(void) {
	printf("OhWordC");

	printf("%f",OhWordC::Math::random());
	return 0;
}
