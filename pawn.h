#pragma once
#include "piece.h"
#include "board.h"
#include "uiDraw.h"

class Pawn : public Piece
{
public:
   Pawn();
   Pawn(int row, int col, bool black);
   std::set<Move> getPossibleMoves(const Board& board);
   void draw(ogstream& gout) const override { gout.drawPawn(position.getLocation(), !isWhite()); }
private:
   friend class TestKing;
   friend class TestPawn;

   bool isValid(const int num);
   //int enPassantTurn;    // Moved to Piece, along with set and get.

};