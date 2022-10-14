/***********************************************************************
 * Source File:
 *     Space
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Space class filling constructors
 ************************************************************************/
#include "space.h"

/***************************************************************************
 * Space
 * will set all the values to the included variables
 ***************************************************************************/
Space::Space(const int& row, const int& col)
{
   position.setRow(row);
   position.setCol(col);
   pieceType = 's';
}

/***************************************************************************
 * Queen
 * will set all the variables to their default values.
 ***************************************************************************/
Space::Space()
{
   position.setRow(0);
   position.setCol(0);
   pieceType = 's';
}