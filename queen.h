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
   Queen(const int &row, const int &col, const bool &whiteColor);
   void draw(ogstream& gout) const override { gout.drawQueen(position.getLocation(), !isWhite()); }
};