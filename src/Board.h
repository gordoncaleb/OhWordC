/*
 * Board.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <stack>
#include <stdio.h>

using namespace std;

enum GameStatus{IN_PLAY,CHECK,CHECKMATE,STALEMATE,TIMES_UP,DRAW,INVALID};
enum PositionStatus{NO_PIECE,ENEMY,FRIEND,OFF_BOARD};

class Board {

	Piece** board;
	GameStatus boardStatus;
	vector<long> validMoves = new vector<long>(100);
	vector<Piece>* pieces = new vector[2];
	vector<Piece>* piecesTaken = new stack[2];
	int* castleRights = new int[2];

	Piece* kings = new Piece[2];
	int** rookStartCols = new int[2][2];
	int* kingCols = new int[2];
	int* materialRow = {0, 7};

	side_t turn;
	RNGTable rngTable;
	vector<Move> moveHistory;
	long hashCode;
	vector<long> hashCodeHistory;
	long* nullMoveInfo = {0, -1, 0};

	long** posBitBoard = new long[6][2];
	long* allPosBitBoard = new long[2];

public:
	Board();
	Board(vector<Piece>* pieces, side_t turn, vector<Move> moveHistory, int** rookStartCols, int* kingCols);

	bool makeMove(long move);
	void movePiece(Piece pieceMoving, int toRow, int toCol, MoveNote note);
	long undoMove();
	void undoMovePiece(Piece pieceMoving, int fromRow, int fromCol, MoveNote note, bool hadMoved);
	void verifyBitBoards();
	bool canUndo();
	vector<long> generateValidMoves();
	vector<long> generateValidMoves(bool sort, long hashMove, long* killerMoves);
	long* makeNullMove();
	PositionStatus checkPiece(int row, int col, side_t player);
	long getLastMoveMade();
	vector<Move> getMoveHistory();
	int getPieceValue(int row, int col);
	int getOpeningPositionValue(Piece piece);
	int getEndGamePositionValue(Piece piece);
	int openingPositionScore(side_t side);
	int endGamePositionScore(side_t side);
	int materialScore(side_t side);
	int castleScore(side_t side);
	int pawnStructureScore(side_t side, int phase);
	int calcGamePhase();
	int staticScore();
	Piece getPiece(int row, int col);
	PieceID getPieceID(int row, int col);
	side_t getPieceSide(int row, int col);
	side_t getTurn();
	void setTurn(side_t turn);
	bool hasPiece(int row, int col);
	bool hasMoved(int row, int col);
	vector<Piece> getPiecesTakenFor(side_t player);
	void initializeCastleSetup();
	bool placePiece(Piece piece, int toRow, int toCol);
	bool isInCheck();
	bool isInCheckMate();
	bool isInStaleMate();
	bool isTimeUp();
	bool isDraw();
	bool isInvalid();
	bool isGameOver();
	void clearBoardStatus();
	GameStatus getBoardStatus();
	void setBoardStatus(GameStatus boardStatus);
	bool farRookHasMoved(side_t player);
	bool nearRookHasMoved(side_t player);
	int getRookStartingCol(side_t side, int near);
	int getKingStartingCol(side_t side);
	bool kingHasMoved(side_t player);
	long farCastleMask(side_t player);
	long nearCastleMask(side_t player);
	Board getCopy();
	string toString();
	string toXML(bool includeHistory);
	long generateHashCode();
	int getHashIndex();
	long getHashCode();
	static long getHashCode(string xmlBoard);
	bool drawByThreeRule();
	bool hasSufficientMaterial();
	void loadPiecesTaken();
	long resolveAlgebraicNotation(string notation);
	static vector<Piece> getFullPieceSet(side_t player);
};

#endif /* BOARD_H_ */
