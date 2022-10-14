#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

class Knight : public Piece
{
public:
   Knight();
   Knight(int row, int col, bool white);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int num);
   void draw(ogstream& gout) const override { gout.drawKnight(position.getLocation(), !isWhite()); }
};

