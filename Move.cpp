/*
 * Move.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: walker
 */

#include "Move.h"
namespace OhWordC {
/**
 * Bit-field 0-2 = toCol 3-5 = toRow 6-8 = fromCol 9-11 = fromRow 12-14 =
 * move note 15 = hadMoved 16 = has piece taken 17-19 = pieceTaken col 20-22
 * = pieceTaken row 23-25 = pieceTaken id 26 = pieceTaken has moved 32-48 =
 * moveValue
 */

Move::Move(int fromRow, int fromCol, int toRow, int toCol) {
	move = 0;
	this(fromRow, fromCol, toRow, toCol, 0, NONE, 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value) {
	move = 0;
	this(fromRow, fromCol, toRow, toCol, value, NONE, 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note) {
	move = 0;
	this(fromRow, fromCol, toRow, toCol, value, note, 0, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken) {
	move = 0;
	this(fromRow, fromCol, toRow, toCol, 0, note, pieceTaken, false);
}

Move::Move(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved) {
	move = Move::moveLong(fromRow, fromCol, toRow, toCol, value, note, pieceTaken, hadMoved);
}

// -------------------------------------------------------

 long Move::moveLong(int fromRow, int fromCol, int toRow, int toCol) {
	return Move::moveLong(fromRow, fromCol, toRow, toCol, 0, NONE, (Piece)0, false);
}

 long Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value) {
	return Move::moveLong(fromRow, fromCol, toRow, toCol, value, NONE, (Piece)0, false);
}

 long Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note) {
	return Move::moveLong(fromRow, fromCol, toRow, toCol, value, note, (Piece)0, false);
}

 long Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken) {
	return Move::moveLong(fromRow, fromCol, toRow, toCol, value, note, pieceTaken, false);
}

 long Move::moveLong(int fromRow, int fromCol, int toRow, int toCol, int value, MoveNote note, Piece pieceTaken, bool hadMoved) {
	long moveLong;

	moveLong = (note << 12) | (fromRow << 9) | (fromCol << 6) | (toRow << 3) | toCol;

	if (hadMoved) {
		moveLong |= hadMovedMask;
	}

	if (pieceTaken != 0) {
		moveLong |= (pieceTaken.getPieceID() << 23) | (pieceTaken.getRow() << 20) | (pieceTaken.getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken.hasMoved()) {
			moveLong |= pieceTakenHasMoved;
		}
	}

	moveLong |= ((long) value) << 32;

	return moveLong;
}

Move::Move(long moveInt) {
	this->move = moveInt;
}

 bool Move::equals(long moveLongA, long moveLongB) {

	if ((moveLongA & fromToMask) == (moveLongB & fromToMask))
		return true;
	else
		return false;
}

 bool Move::fromEquals(long moveLongA, long moveLongB) {

	if ((moveLongA & fromMask) == (moveLongB & fromMask))
		return true;
	else
		return false;
}

 bool Move::toEquals(long moveLongA, long moveLongB) {

	if ((moveLongA & toMask) == (moveLongB & toMask))
		return true;
	else
		return false;
}

long Move::setNote(MoveNote note) {
	this->move &= notNoteMask;
	this->move |= (note << 12);

	return move;
}

 long Move::setNote(long moveLong, MoveNote note) {
	moveLong &= notNoteMask;
	moveLong |= (note << 12);

	return moveLong;
}

MoveNote Move::getNote() {
	return ((this->move >> 12) & 0x7);
}

 MoveNote Move::getNote(long moveLong) {
	return ((move >> 12) & 0x7);
}

int Move::getFromRow() {
	return ((move >> 9) & 0x7);
}

 int Move::getFromRow(long moveLong) {
	return ((move >> 9) & 0x7);
}

int Move::getFromCol() {
	return ((move >> 6) & 0x7);
}

 int Move::getFromCol(long moveLong) {
	return ((move >> 6) & 0x7);
}

int Move::getToRow() {
	return ((move >> 3) & 0x7);
}

 int Move::getToRow(long moveLong) {
	return ((move >> 3) & 0x7);
}

int Move::getToCol() {
	return (int) (move & 0x7);
}

 int Move::getToCol(long moveLong) {
	return (int) (move & 0x7);
}

int Move::getValue() {
	return (int) (move >> 32);
}

 int Move::getValue(long moveLong) {
	return (int) (move >> 32);
}

long Move::setValue(int value) {
	move = move & 0xFFFFFFFFL;
	move |= ((long) value) << 32;

	return move;
}

 long Move::setValue(long moveLong, int value) {
	moveLong = moveLong & 0xFFFFFFFFL;

	moveLong |= ((long) value) << 32;

	return moveLong;
}

long Move::setPieceTaken(Piece pieceTaken) {
	move &= notPieceTaken;
	if (pieceTaken != 0) {
		move |= (pieceTaken.getPieceID() << 23) | (pieceTaken.getRow() << 20) | (pieceTaken.getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken.hasMoved()) {
			move |= pieceTakenHasMoved;
		}
	}

	return move;
}

 long Move::setPieceTaken(long moveLong, Piece pieceTaken) {
	moveLong &= notPieceTaken;
	if (pieceTaken != 0) {
		moveLong |= (pieceTaken.getPieceID() << 23) | (pieceTaken.getRow() << 20) | (pieceTaken.getCol() << 17) | hasPieceTakenMask;

		if (pieceTaken.hasMoved()) {
			moveLong |= pieceTakenHasMoved;
		}
	}

	return moveLong;
}

bool Move::hadMoved() {
	return ((move & hadMovedMask) != 0);
}

 bool Move::hadMoved(long moveLong) {
	return ((moveLong & hadMovedMask) != 0);
}

long Move::setHadMoved(bool hadMoved) {
	if (hadMoved) {
		move |= hadMovedMask;
	} else {
		move &= ~hadMovedMask;
	}

	return move;
}

 long Move::setHadMoved(long moveLong, bool hadMoved) {
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

 bool Move::hasPieceTaken(long moveLong) {
	return ((moveLong & hasPieceTakenMask) != 0);
}

bool Move::getPieceTakenHasMoved() {
	return ((move & pieceTakenHasMoved) != 0);
}

 bool Move::getPieceTakenHasMoved(long moveLong) {
	return ((moveLong & pieceTakenHasMoved) != 0);
}

int Move::getPieceTakenRow() {
	return (int) ((move >> 20) & 0x7);
}

 int Move::getPieceTakenRow(long moveLong) {
	return (int) ((moveLong >> 20) & 0x7);
}

int Move::getPieceTakenCol() {
	return (int) ((move >> 17) & 0x7);
}

 int Move::getPieceTakenCol(long moveLong) {
	return (int) ((moveLong >> 17) & 0x7);
}

PieceID Move::getPieceTakenID() {
	return ((move >> 23) & 0x7);
}

 PieceID Move::getPieceTakenID(long moveLong) {
	return ((moveLong >> 23) & 0x7);
}

Move Move::getCopy() {
	return new Move(move);
}

long Move::getMoveLong() {
	return move;
}

Move::~Move() {
// TODO Auto-generated destructor stub
}
}

