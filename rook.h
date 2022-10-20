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

/***********************************
 * Rook Class
 ***********************************/
class Rook : public Piece
{
public:
   Rook();
   Rook(const int &row, const int &col, const bool &whiteColor);
   void draw(ogstream& gout) const;
   friend class TestKing;
};