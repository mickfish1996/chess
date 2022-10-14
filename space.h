/***********************************************************************
 * Header File:
 *     Space
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines the derived class Space and all its needed methods
 ************************************************************************/
#pragma once
#include "piece.h"

 /******************************************************************************
  * Space
  * The Queen class contains information needed specifically for Space.
  ******************************************************************************/
class Space :
   public Piece
{
private:
   //Position position;
public:
   Space(const int& row, const int& col);
   Space();
   void draw(ogstream gout) {}
   //void setRow(const int &r) { position.setRow(r); }
   //void setCol(const int &c) { position.setCol(c); }
};