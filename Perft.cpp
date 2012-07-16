#include "StdAfx.h"
#include "Perft.h"

namespace OhWordC{
	Perft::Perft(void)
	{
		for(int i=0;i<20;i++){
			level[i] = 0;
		}
	}

	void Perft::grow(int depth, Board * board) {
		level[depth]++;
		if (depth > 0) {
			board->makeNullMove();

			vector<__int64> * moves = new vector<__int64>(board->generateValidMoves(true, 0, (__int64*)0));

			for (int i = 0; i < (int)moves->size(); i++) {
				board->makeMove(moves->at(i));
				
				//printf("Move made :\n%s",board->toString().c_str());

				grow(depth - 1,board);
				board->undoMove();

				//printf("Move unmade :\n%s",board->toString().c_str());
			}
		}

	}
	Perft::~Perft(void)
	{
	}
}