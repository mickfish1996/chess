/******************************************************************************
* KING
* The King class contains information needed specifically for King.
******************************************************************************/

#pragma once
#include "piece.h"
#include "space.h"
#include "uiDraw.h"
#include <vector>

class King :
   public Piece
{
private:
   /*const char pieceType = 'k';*/
public:
   King();
   King(int row, int col, bool white);
   std::set<Move> getPossibleMoves(const Board& board);
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawKing(position.getLocation(), isWhite()); }

   friend class TestKing;
};

