/*
 * Move.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "stdafx.h"
namespace OhWordC {

int Move::hadMovedMask = 1 << 15;
int Move::hasPieceTakenMask = 1 << 16;
int Move::pieceTakenHasMoved = 1 << 26;
int Move::fromToMask = 0xFFF;
int Move::fromMask = 0xFC0;
int Move::toMask = 0x3F;
int Move::notNoteMask = ~(0x7000);
int Move::notPieceTaken = ~(0x7FF << 16);

/**
 * Bit-field 0-2 = toCol 3-5 = toRow 6-8 = fromCol 9-11 = fromRow 12-14 =
 * move note 15 = hadMoved 16 = has piece taken 17-19 = pieceTaken col 20-22
 * = pieceTaken row 23-25 = pieceTaken id 26 = pieceTaken has moved 32-48 =
 * moveValue
 */

Move::Move(int fromRow, int fromCol, int toRow, int toCol) {
	setMoveLong(fromRow, fromCol, toRow, toCol, (MoveNote) 0, NONE, (Piece*) 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value) {
	setMoveLong(fromRow, fromCol, toRow, toCol, value, NONE, (Piece *) 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note) {
	setMoveLong(fromRow, fromCol, toRow, toCol, value, note, (Piece *) 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken) {
	setMoveLong(fromRow, fromCol, toRow, toCol, 0, note, &pieceTaken, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved) {
	setMoveLong(fromRow, fromCol, toRow, toCol, value, note, &pieceTaken, hadMoved);
}

void Move::setMoveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece * pieceTaken, bool hadMoved) {
	move = moveLong(fromRow, fromCol, toRow, toCol, value, note, pieceTaken, hadMoved);
}

// -------------------------------------------------------

__int64 Move::moveLong(int fromRow, int fromCol, int toRow, int toCol) {
	return moveLong(fromRow, fromCol, toRow, toCol, 0, NONE, (Piece*) 0, false);
}

__int64 Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value) {
	return moveLong(fromRow, fromCol, toRow, toCol, value, NONE, (Piece*) 0, false);
}

__int64 Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note) {
	return moveLong(fromRow, fromCol, toRow, toCol, value, note, (Piece*) 0, false);
}

__int64 Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece * pieceTaken) {
	return moveLong(fromRow, fromCol, toRow, toCol, value, note, pieceTaken, false);
}

__int64 Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece * pieceTaken, bool hadMoved) {
	__int64 moveLong;

	moveLong = (note << 12) | (fromRow << 9) | (fromCol << 6) | (toRow << 3) | toCol;

	if (hadMoved) {
		moveLong |= hadMovedMask;
	}

	if (pieceTaken != 0) {
		moveLong |= (pieceTaken->getPieceID() << 23) | (pieceTaken->getRow() << 20) | (pieceTaken->getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken->hasMoved()) {
			moveLong |= pieceTakenHasMoved;
		}
	}

	moveLong |= ((__int64) value) << 32;

	return moveLong;
}

Move::Move(__int64 moveInt) {
	move = moveInt;
}

bool Move::equals(__int64 moveLongA, __int64 moveLongB) {

	if ((moveLongA & fromToMask) == (moveLongB & fromToMask))
		return true;
	else
		return false;
}

bool Move::fromEquals(__int64 moveLongA, __int64 moveLongB) {

	if ((moveLongA & fromMask) == (moveLongB & fromMask))
		return true;
	else
		return false;
}

bool Move::toEquals(__int64 moveLongA, __int64 moveLongB) {

	if ((moveLongA & toMask) == (moveLongB & toMask))
		return true;
	else
		return false;
}

//string Move::toXML() {
//	return Move::toXML(moveLong);
//}
//
//string Move::toXML(__int64 moveLong) {
//
//	string xmlMove = "";
//
//	xmlMove += "<move>\n";
//
//	xmlMove += "<from>" + getFromRow(moveLong) + "," + getFromCol(moveLong) + "</from>\n";
//	xmlMove += "<to>" + getToRow(moveLong) + "," + getToCol(moveLong) + "</to>\n";
//
//	if (hadMoved(moveLong)) {
//		xmlMove += "<had_moved>" + hadMoved(moveLong) + "</had_moved>\n";
//	}
//
//	MoveNote note = getNote(moveLong);
//	if (note != MoveNote.NONE) {
//		xmlMove += "<note>" + note.toString() + "</note>\n";
//	}
//
//	if (hasPieceTaken(moveLong)) {
//		xmlMove += new Piece(getPieceTakenID(moveLong), NULL, getPieceTakenRow(moveLong), getPieceTakenCol(moveLong),getPieceTakenHasMoved(moveLong)).toXML();
//	}
//
//	xmlMove += "</move>\n";
//
//	return xmlMove;
//}

__int64 Move::setNote(MoveNote note) {
	this->move &= notNoteMask;
	this->move |= (note << 12);

	return move;
}

__int64 Move::setNote(__int64 moveLong, MoveNote note) {
	moveLong &= notNoteMask;
	moveLong |= (note << 12);

	return moveLong;
}

MoveNote Move::getNote() {
	return (MoveNote) ((move >> 12) & 0x7);
}

MoveNote Move::getNote(__int64 moveLong) {
	return (MoveNote) ((moveLong >> 12) & 0x7);
}

int Move::getFromRow() {
	return ((move >> 9) & 0x7);
}

int Move::getFromRow(__int64 moveLong) {
	return ((moveLong >> 9) & 0x7);
}

int Move::getFromCol() {
	return ((move >> 6) & 0x7);
}

int Move::getFromCol(__int64 moveLong) {
	return ((moveLong >> 6) & 0x7);
}

int Move::getToRow() {
	return ((move >> 3) & 0x7);
}

int Move::getToRow(__int64 moveLong) {
	return ((moveLong >> 3) & 0x7);
}

int Move::getToCol() {
	return (int) (move & 0x7);
}

int Move::getToCol(__int64 moveLong) {
	return (int) (moveLong & 0x7);
}

int Move::getValue() {
	return (int) (move >> 32);
}

int Move::getValue(__int64 moveLong) {
	return (int) (moveLong >> 32);
}

__int64 Move::setValue(int value) {
	move = move & 0xFFFFFFFFL;
	move |= ((__int64) value) << 32;

	return move;
}

__int64 Move::setValue(__int64 moveLong, int value) {
	moveLong = moveLong & 0xFFFFFFFFL;

	moveLong |= ((__int64) value) << 32;

	return moveLong;
}

__int64 Move::setPieceTaken(Piece* pieceTaken) {
	move &= notPieceTaken;
	if (pieceTaken != 0) {
		move |= (pieceTaken->getPieceID() << 23) | (pieceTaken->getRow() << 20) | (pieceTaken->getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken->hasMoved()) {
			move |= pieceTakenHasMoved;
		}
	}

	return move;
}

__int64 Move::setPieceTaken(__int64 moveLong, Piece* pieceTaken) {
	moveLong &= notPieceTaken;
	if (pieceTaken != 0) {
		moveLong |= (pieceTaken->getPieceID() << 23) | (pieceTaken->getRow() << 20) | (pieceTaken->getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken->hasMoved()) {
			moveLong |= pieceTakenHasMoved;
		}
	}

	return moveLong;
}

bool Move::hadMoved() {
	return ((move & hadMovedMask) != 0);
}

bool Move::hadMoved(__int64 moveLong) {
	return ((moveLong & hadMovedMask) != 0);
}

__int64 Move::setHadMoved(bool hadMoved) {
	if (hadMoved) {
		move |= hadMovedMask;
	} else {
		move &= ~hadMovedMask;
	}

	return move;
}

__int64 Move::setHadMoved(__int64 moveLong, bool hadMoved) {
	if (hadMoved) {
		moveLong |= hadMovedMask;
	} else {
		moveLong &= ~hadMovedMask;
	}

	return moveLong;
}

bool Move::hasPieceTaken() {
	return ((move & hasPieceTakenMask) != 0);
}

bool Move::hasPieceTaken(__int64 moveLong) {
	return ((moveLong & hasPieceTakenMask) != 0);
}

bool Move::getPieceTakenHasMoved() {
	return ((move & pieceTakenHasMoved) != 0);
}

bool Move::getPieceTakenHasMoved(__int64 moveLong) {
	return ((moveLong & pieceTakenHasMoved) != 0);
}

int Move::getPieceTakenRow() {
	return (int) ((move >> 20) & 0x7);
}

int Move::getPieceTakenRow(__int64 moveLong) {
	return (int) ((moveLong >> 20) & 0x7);
}

int Move::getPieceTakenCol() {
	return (int) ((move >> 17) & 0x7);
}

int Move::getPieceTakenCol(__int64 moveLong) {
	return (int) ((moveLong >> 17) & 0x7);
}

PieceID Move::getPieceTakenID() {
	return (PieceID)((move >> 23) & 0x7);
}

PieceID Move::getPieceTakenID(__int64 moveLong) {
	return (PieceID)((moveLong >> 23) & 0x7);
}

Move * Move::getCopy() {
	return new Move(move);
}

__int64 Move::getMoveLong() {
	return move;
}

Move::~Move() {
// TODO Auto-generated destructor stub
}
}

