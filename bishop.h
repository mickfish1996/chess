#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

class Bishop : public Piece
{
public:
   Bishop();
   Bishop(int row, int col, bool white);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawBishop(position.getLocation(), isWhite()); }
};

