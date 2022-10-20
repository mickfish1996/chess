/***********************************************************************
 * Header File:
 *     King
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class Rook and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"

/************************************************************************
 * Rook Class
 * The Rook class contains information needed specifically for Rook.
 ************************************************************************/
class Rook : public Piece
{
public:
   Rook();
   Rook(const int &row, const int &col, const bool &whiteColor);
   void draw(ogstream& gout) const { gout.drawRook(position.getLocation(), !isWhite()); };
   friend class TestKing;
};