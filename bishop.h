/***********************************************************************
 * Header File:
 *     Bishop
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class bishop and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"
#include "uiDraw.h"
#include <vector>

/*************************************************************************
 * Bishop
 * The Derived class Bishop holding its constructors and other needed
 * methods.
 *************************************************************************/
class Bishop : public Piece
{
public:
   Bishop();
   Bishop(const int& row, const int& col, const bool& whiteColor);
   std::set<Move> getPossibleMoves(const Board& board) override;
   bool isValid(const int row);
   void draw(ogstream& gout) const override { gout.drawBishop(position.getLocation(), !isWhite()); }
};

