/*
 * Piece.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Piece.h"
namespace OhWordC {
Piece::Piece() {
	this->id = -1;
	this->moved = false;
	this->player = -1;
	this->row = -1;
	this->col = -1;
	this->blockingVector = -1;
}

Piece::Piece(PieceID id, side_t player, int row, int col, bool moved) {
	this->id = id;
	this->moved = moved;
	this->player = player;
	this->row = row;
	this->col = col;
	this->blockingVector = -1;
}

int Piece::getRow() {
	return row;
}

int Piece::getCol() {
	return col;
}

unsigned long Piece::getBit() {
	return BitBoard::getMask(row, col);
}

void Piece::setPos(int row, int col) {
	this->row = row;
	this->col = col;
}

void Piece::move(long newMove) {
	setPos(Move::getToRow(newMove), Move::getToCol(newMove));
	moved = true;
}

void Piece::reverseMove(long newMove) {
	setPos(Move::getFromRow(newMove), Move::getFromCol(newMove));
}

side_t Piece::getSide() {
	return player;
}

bool Piece::hasMoved() {
	return moved;
}

void Piece::setMoved(bool moved) {
	this->moved = moved;
}

void Piece::setBlockingVector(long blockingVector) {
	this->blockingVector = blockingVector;
}

void Piece::clearBlocking() {
	blockingVector = -1;
}

long Piece::getBlockingVector() {
	return blockingVector;
}

static PieceID Piece::charIDtoPieceID(char type) {

	PieceID id;

	switch (type) {
	case 'R':
		id = ROOK;
		break;
	case 'N':
		id = KNIGHT;
		break;
	case 'B':
		id = BISHOP;
		break;
	case 'Q':
		id = QUEEN;
		break;
	case 'K':
		id = KING;
		break;
	case 'P':
		id = PAWN;
		break;
	default:
		id = -1;
		break;
	}

	return id;
}

bool Piece::equals(Piece piece) {

	if (piece == 0) {
		return false;
	}

	if (piece.getRow() == row && piece.getCol() == col && piece.getSide() == player && piece.getPieceID() == this->getPieceID()) {
		return true;
	} else {
		return false;
	}
}

bool Piece::isValidMove(int toRow, int toCol, long * nullMoveInfo) {
	long mask = BitBoard::getMask(toRow, toCol);

	if ((mask & nullMoveInfo[1] & blockingVector) != 0) {
		return true;
	} else {
		return false;
	}
}

PieceID Piece::getPieceID() {
	return id;
}

void Piece::setPieceID(PieceID id) {
	this->id = id;
}

void Piece::generateValidMoves(Board* board, long* nullMoveInfo, long* posBitBoard, vector<long> validMoves) {

	switch (id) {
	case ROOK:
		Rook::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	case KNIGHT:
		Knight::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	case BISHOP:
		Bishop::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	case QUEEN:
		Queen::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	case KING:
		King::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	case PAWN:
		Pawn::generateValidMoves(this, board, nullMoveInfo, posBitBoard, validMoves);
		break;
	default:
		break;
	}

}

void Piece::getNullMoveInfo(Board* board, long* nullMoveInfo, long updown, long left, long right, long kingBitBoard, long kingCheckVectors, long friendly) {
	switch (id) {
	case ROOK:
		Rook::getNullMoveInfo(this, board, nullMoveInfo, updown, left, right, kingBitBoard, kingCheckVectors, friendly);
		break;
	case KNIGHT:
		//Knight.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case BISHOP:
		Bishop::getNullMoveInfo(this, board, nullMoveInfo, updown, left, right, kingBitBoard, kingCheckVectors, friendly);
		break;
	case QUEEN:
		Queen::getNullMoveInfo(this, board, nullMoveInfo, updown, left, right, kingBitBoard, kingCheckVectors, friendly);
		break;
	case KING:
		//King.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case PAWN:
		//Pawn.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	}
}

void Piece::getNullMoveInfo(Board* board, long* nullMoveBitBoards) {
	switch (id) {
	case ROOK:
		Rook::getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case KNIGHT:
		//Knight.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case BISHOP:
		Bishop::getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case QUEEN:
		Queen::getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case KING:
		//King.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	case PAWN:
		//Pawn.getNullMoveInfo(this, board, nullMoveBitBoards);
		break;
	}
}

Piece Piece::getCopy() {
	return new Piece(id, player, row, col, moved);
}

Piece::~Piece() {
// TODO Auto-generated destructor stub
}
}
