/***********************************************************************
 * Source File:
 *     Queen
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Queen class filling constructors and
 *     defining all methods that are needed.
 ************************************************************************/
#include "queen.h"

/***************************************************************************
 * DEFAULT CONSTRUCTOR
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
Queen::Queen() : Piece()
{
   pieceType = 'q';
   moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

/***************************************************************************
 * CONSTRUCTOR
 * will set all the values to the included variables
 ***************************************************************************/
Queen::Queen(const int &row, const int &col, const bool &whiteColor)
   : Piece(row, col, whiteColor)
{
   pieceType = 'q';
   moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}
