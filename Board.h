/*
 * Board.h
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#ifndef BOARD_H_
#define BOARD_H_


using namespace std;

namespace OhWordC {
enum GameStatus{IN_PLAY,CHECK,CHECKMATE,STALEMATE,TIMES_UP,DRAW,INVALID};
enum PositionStatus{NO_PIECE,ENEMY,FRIEND,OFF_BOARD};

class Board {

	Piece * board[8][8];
	GameStatus boardStatus;
	vector<__int64> validMoves;
	vector<Piece*> * pieces [2];
	vector<Piece*> * piecesTaken [2];
	int castleRights [2];

	Piece * kings[2];
	int rookStartCols [2][2];
	int kingCols [2];
	int materialRow [2];

	side_t turn;
	RNGTable * rngTable;
	vector<Move*> * moveHistory;
	__int64 hashCode;
	vector<__int64> hashCodeHistory;
	__int64 nullMoveInfo [3];

	__int64 posBitBoard [6][2];
	__int64 allPosBitBoard [2];

public:

	Board();
	Board(vector<Piece*>* pieces[2], side_t turn, vector<Move*> * moveHistory, int rookStartCols[2][2], int kingCols[2]);

	bool makeMove(__int64 move);
	void movePiece(Piece * pieceMoving, int toRow, int toCol, MoveNote note);
	__int64 undoMove();
	void undoMovePiece(Piece * pieceMoving, int fromRow, int fromCol, MoveNote note, bool hadMoved);
	void verifyBitBoards();
	bool canUndo();
	vector<__int64> generateValidMoves();
	vector<__int64> generateValidMoves(bool sort, __int64 hashMove, __int64 killerMoves[]);
	__int64* makeNullMove();
	PositionStatus checkPiece(int row, int col, side_t player);
	__int64 getLastMoveMade();
	vector<Move*> * getMoveHistory();
	int getPieceValue(int row, int col);
	int getOpeningPositionValue(Piece* piece);
	int getEndGamePositionValue(Piece* piece);
	int openingPositionScore(side_t side);
	int endGamePositionScore(side_t side);
	int materialScore(side_t side);
	int castleScore(side_t side);
	int pawnStructureScore(side_t side, int phase);
	int calcGamePhase();
	int staticScore();
	Piece * getPiece(int row, int col);
	PieceID getPieceID(int row, int col);
	side_t getPieceSide(int row, int col);
	side_t getTurn();
	void setTurn(side_t turn);
	bool hasPiece(int row, int col);
	bool hasMoved(int row, int col);
	vector<Piece*> * getPiecesTakenFor(side_t player);
	void initializeCastleSetup();
	bool placePiece(Piece * piece, int toRow, int toCol);
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
	__int64 farCastleMask(side_t player);
	__int64 nearCastleMask(side_t player);
	Board * getCopy();
	string toString();
	string toXML(bool includeHistory);
	__int64 generateHashCode();
	int getHashIndex();
	__int64 getHashCode();
	static __int64 getHashCode(string xmlBoard);
	bool drawByThreeRule();
	bool hasSufficientMaterial();
	void loadPiecesTaken();
	__int64 resolveAlgebraicNotation(string notation);
	static vector<Piece*> * getFullPieceSet(side_t player);
};

}
#endif /* BOARD_H_ */
