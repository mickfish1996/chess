/***********************************************************************
 * Header File:
 *     Queen
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class Queen and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

/******************************************************************************
 * Queen
 * The Queen class contains information needed specifically for Queen.
 ******************************************************************************/
class Queen : public Piece
{
public:
   Queen();
   Queen(int row, int col, bool white);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawQueen(position.getLocation(), !isWhite()); }
};

