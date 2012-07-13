#include "StdAfx.h"
#include "Perft.h"

namespace OhWordC{
	Perft::Perft(void)
	{
	}

	void Perft::grow(int depth, Board * board) {
		level[depth]++;
		if (depth > 0) {
			printf("Making Nullmove");
			board->makeNullMove();
			printf("Null move made");

			vector<__int64> * moves = new vector<__int64>(board->generateValidMoves(true, 0, (__int64*)0));
			printf("Moves generated");

			for (int i = 0; i < (int)moves->size(); i++) {
				board->makeMove(moves->at(i));
				printf("Move made");
				grow(depth - 1,board);
				board->undoMove();
				printf("Move undone");
			}
		}

	}
	Perft::~Perft(void)
	{
	}
}