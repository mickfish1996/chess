/***********************************************************************
 * Header File:
 *     Pawn
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class Pawn and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"
#include "board.h"
#include "uiDraw.h"

 /******************************************************************************
 * Pawn
 * The Pawn class contains information needed specifically for Pawn.
 ******************************************************************************/
class Pawn : public Piece
{
public:
   Pawn();
   Pawn(const int &row, const int &col, const bool &whiteColor);
   std::set<Move> getPossibleMoves(const Board& board);
   void draw(ogstream& gout) const override { gout.drawPawn(position.getLocation(), !isWhite()); }
private:
   friend class TestKing;
   friend class TestPawn;

   bool isValid(const int num);
};