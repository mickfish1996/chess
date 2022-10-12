#pragma once
#include "piece.h"
#include "board.h"

class Pawn : public Piece
{
public:
   Pawn();
private:
   friend class TestKing;
   friend class TestPawn;
   //int enPassantTurn;    // Moved to Piece, along with set and get.
public:
   std::set<Move> getPossibleMoves(const Board& board);
};