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
public:
   Space();
   Space(const int& row, const int& col);
   void draw(ogstream gout) {}
};