/*
 * Piece.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {
Piece::Piece() {
	this->id = (PieceID) -1;
	this->moved = false;
	this->player = (side_t) -1;
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

unsigned __int64 Piece::getBit() {
	return BitBoard::getMask(row, col);
}

void Piece::setPos(int row, int col) {
	this->row = row;
	this->col = col;
}

void Piece::move(__int64 newMove) {
	setPos(Move::getToRow(newMove), Move::getToCol(newMove));
	moved = true;
}

void Piece::reverseMove(__int64 newMove) {
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

void Piece::setBlockingVector(__int64 blockingVector) {
	this->blockingVector = blockingVector;
}

void Piece::clearBlocking() {
	blockingVector = -1;
}

__int64 Piece::getBlockingVector() {
	return blockingVector;
}

string Piece::toString() {
	string id;

	if (this->getSide() == BLACK) {
		id = this->getCharID();
	} else {
		id = this->getCharID() + 32;
	}

	return id;
}

string Piece::toXML() {

	string hasMoved;

	if(this->hasMoved()){
		hasMoved = "true";
	}else{
		hasMoved = "false";
	}

	char buf[500];
	sprintf_s(buf,"<piece>\n<id>%s</id>\n<has_moved>%s</has_moved>\n<position>%d,%d</position>\n</piece>\n",this->toString().c_str(),hasMoved.c_str(),this->getRow(),this->getCol());

	string xmlPiece(buf);

	return xmlPiece;
}

PieceID Piece::charIDtoPieceID(char type) {

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
		id = (PieceID) -1;
		break;
	}

	return id;
}

bool Piece::equals(Piece * piece) {

	if (piece == 0) {
		return false;
	}

	if (piece->getRow() == row && piece->getCol() == col && piece->getSide() == player && piece->getPieceID() == this->getPieceID()) {
		return true;
	} else {
		return false;
	}
}

bool Piece::isValidMove(int toRow, int toCol, __int64 * nullMoveInfo) {
	__int64 mask = BitBoard::getMask(toRow, toCol);

	if ((mask & nullMoveInfo[1] & blockingVector) != 0) {
		return true;
	} else {
		return false;
	}
}

char Piece::getCharID() {
	switch (id) {
	case ROOK:
		return Rook::getStringID().c_str()[0];
		break;
	case KNIGHT:
		return Knight::getStringID().c_str()[0];
		break;
	case BISHOP:
		return Bishop::getStringID().c_str()[0];
		break;
	case QUEEN:
		return Queen::getStringID().c_str()[0];
		break;
	case KING:
		return King::getStringID().c_str()[0];
		break;
	case PAWN:
		return Pawn::getStringID().c_str()[0];
		break;
	default:
		return '0';
	}

}

PieceID Piece::getPieceID() {
	return id;
}

void Piece::setPieceID(PieceID id) {
	this->id = id;
}

void Piece::generateValidMoves(Board* board, __int64* nullMoveInfo, __int64* posBitBoard, vector<__int64> * validMoves) {

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

void Piece::getNullMoveInfo(Board* board, __int64* nullMoveInfo, __int64 updown, __int64 left, __int64 right, __int64 kingBitBoard, __int64 kingCheckVectors, __int64 friendly) {
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

void Piece::getNullMoveInfo(Board* board, __int64* nullMoveBitBoards) {
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

Piece* Piece::getCopy() {
	return new Piece(this->id, this->player, this->row, this->col, this->moved);
}

Piece::~Piece() {
// TODO Auto-generated destructor stub
}
}
