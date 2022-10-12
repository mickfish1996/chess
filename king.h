/******************************************************************************
* KING
* The King class contains information needed specifically for King.
******************************************************************************/

#pragma once
#include "piece.h"
#include "space.h"
#include <vector>

class King :
   public Piece
{
private:
   /*const char pieceType = 'k';*/
public:
   King();
   std::set<Move> getPossibleMoves(const Board& board);
   bool isValid(const int row);

   friend class TestKing;
};

