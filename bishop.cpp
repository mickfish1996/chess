/***********************************************************************
 * Source File:
 *     Bishop
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the bishop piece so that it can be seen and moved 
 *     across the board..
 ************************************************************************/
#include "bishop.h"

/***************************************************************************
 * DEFAULT CONSTRUCTOR
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
Bishop::Bishop() : Piece()
{
   pieceType = 'b';
   moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };
}

/***************************************************************************
 * CONSTRUCTOR
 * will set all the values to the included variables
 ***************************************************************************/
Bishop::Bishop(const int &row, const int &col, const bool &whiteColor) 
   : Piece(row, col, whiteColor)
{
   pieceType = 'b';
   moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };
}