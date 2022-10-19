/***********************************
* Rook Class
***********************************/
#pragma once
#include "piece.h"

class Rook : public Piece
{
public:
   Rook();
   Rook(const int &row, const int &col, const bool &whiteColor);
   void draw(ogstream& gout) const;
   std::set<Move> getPossibleMoves(const Board& board) override;

   friend class TestKing;
};