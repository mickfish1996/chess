/***********************************************************************
 * Header File:
 *     King
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class King and all its needed methods
 ************************************************************************/

#pragma once
#include "piece.h"
#include "space.h"
#include "uiDraw.h"
#include <vector>

/******************************************************************************
* KING
* The King class contains information needed specifically for King.
******************************************************************************/

class King :
   public Piece
{
private:
   bool castleK = false;
   bool castleQ = false;
public:
   King();
   King(const int &row, const int &col, const bool &whiteColor);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawKing(position.getLocation(), !isWhite()); }

   friend class TestKing;
};