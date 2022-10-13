#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

class Queen : public Piece
{
public:
   Queen();
   Queen(int row, int col, bool white);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawQueen(position.getLocation(), !isWhite()); }
};

