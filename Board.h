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

	Piece ** board;
	GameStatus boardStatus;
	vector<long> validMoves;
	vector<Piece> pieces [2];
	vector<Piece> piecesTaken [2];
	int castleRights [2];

	Piece kings[2];
	int rookStartCols [2][2];
	int kingCols [2];
	int materialRow [2];

	side_t turn;
	RNGTable rngTable;
	vector<Move> moveHistory;
	long hashCode;
	vector<long> hashCodeHistory;
	long nullMoveInfo [3];

	long posBitBoard [6][2];
	long allPosBitBoard [2];

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

}
#endif /* BOARD_H_ */
