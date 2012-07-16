/*
 * BoardMaker.h
 *
 *  Created on: Jul 7, 2012
 *      Author: Caleb
 */

#ifndef BOARDMAKER_H_
#define BOARDMAKER_H_

using namespace std;
namespace OhWordC {

class BoardMaker {
public:
	BoardMaker();
	static Board * getStandardChessBoard();
	static Board * getRandomChess960Board();
	static Board * makeBoard(int r1, int r2, int r3, int r4, int r5);
	static int ithEmptyPosition(int i, PieceID setup[8]);
	static int rollDie(int dieSize);
	virtual ~BoardMaker();
};

} /* namespace OhWordC */
#endif /* BOARDMAKER_H_ */
