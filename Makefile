#Make file written by Caleb
#8-7-2012
INCLUDES = -I ./
 
CC = g++ -g -Wall
CFLAGS = -c $(INCLUDES)

all : OhWordC
	
OhWordC : OhWordC.o Side.o Math.o Piece.o Move.o PositionBonus.o SecureRandom.o Values.o RNGTable.o BitBoard.o BoardMaker.o  Bishop.o Rook.o Knight.o Queen.o King.o Pawn.o Board.o
	$(CC) OhWordC.o Math.o -o OhWordC
OhWordC.o : OhWordC.cpp
	$(CC) $(CFLAGS) OhWordC.cpp
Math.o : Math.cpp
	$(CC) $(CFLAGS) Math.cpp
Move.o : Move.cpp
	$(CC) $(CFLAGS) Move.cpp
Piece.o : Piece.cpp
	$(CC) $(CFLAGS) Piece.cpp
PositionBonus.o : PositionBonus.cpp
	$(CC) $(CFLAGS) PositionBonus.cpp
SecureRandom.o : SecureRandom.cpp
	$(CC) $(CFLAGS) SecureRandom.cpp
Side.o : Side.cpp
	$(CC) $(CFLAGS) Side.cpp
Values.o : Values.cpp
	$(CC) $(CFLAGS) Values.cpp
RNGTable.o : RNGTable.cpp
	$(CC) $(CFLAGS) RNGTable.cpp
BitBoard.o : BitBoard.cpp
	$(CC) $(CFLAGS) BitBoard.cpp
Board.o : Board.cpp
	$(CC) $(CFLAGS) Board.cpp
BoardMaker.o : BoardMaker.cpp
	$(CC) $(CFLAGS) BoardMaker.cpp
Bishop.o : Bishop.cpp
	$(CC) $(CFLAGS) Bishop.cpp
Rook.o : Rook.cpp
	$(CC) $(CFLAGS) Rook.cpp
Knight.o : Knight.cpp
	$(CC) $(CFLAGS) Knight.cpp
Queen.o : Queen.cpp
	$(CC) $(CFLAGS) Queen.cpp
King.o : King.cpp
	$(CC) $(CFLAGS) King.cpp
Pawn.o : Pawn.cpp
	$(CC) $(CFLAGS) Pawn.cpp

clean :
	rm -f *.o