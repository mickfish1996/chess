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
 * DEFAULT CONSTRUCTOR
 * will set all the variables to their default values.
 ***************************************************************************/
Space::Space() : Piece()
{
   pieceType = 's';
}

/***************************************************************************
 * CONSTRUCTOR
 * will set all the values to the included variables
 ***************************************************************************/
Space::Space(const int& row, const int& col)
   : Piece(row, col, true)
{
   pieceType = 's';
}