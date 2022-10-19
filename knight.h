/***********************************************************************
 * Header File:
 *     Knight
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class knight and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

/******************************************************************************
* Knight
* The Knight class contains information needed specifically for Knight.
******************************************************************************/
class Knight : public Piece
{
public:
   Knight();
   Knight(const int &row, const int &col, const bool &whiteColor);
   std::set<Move> getPossibleMoves(const Board& board) override;
   void draw(ogstream& gout) const override { gout.drawKnight(position.getLocation(), !isWhite()); }
};

