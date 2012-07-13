// OhWordC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <time.h>

using namespace OhWordC;

int _tmain(int argc, _TCHAR* argv[]){

	printf("Hello world\n");

	Perft * p = new Perft();

	printf("Perft made\n");

	time_t t1 = time(NULL);

	printf("t1=%d\n",t1);

	Board * board = BoardMaker::getStandardChessBoard();

	printf("standard board made\n");

	p->grow(5,board);

	time_t t2 = time(NULL);

	printf("Took %dms", (t2 - t1));

	for (int i = 0; i < 20; i++) {
		printf("Level %d:%d",i,p->level[i]);
		if (p->level[i] == 0) {
			break;
		}
	}

	return 0;
}

