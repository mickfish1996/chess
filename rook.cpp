/***********************************************************************
 * Source File:
 *     Rook
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Rook class filling constructors along with all other 
 *     methods not able to fit in the header file.
 ************************************************************************/
#include "rook.h"

/*********************************************************************
 * DEFAULT CONSTRUCTOR
 * Will set all vaues to a default value.
 *********************************************************************/
Rook::Rook() : Piece()
{
   pieceType = 'r';
   moveSet = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

/*********************************************************************
 * NON-DEFAULT CONSTRUCTOR
 * Will set all vaues to a default value. and will set the position
 * and the color of the piece
 *********************************************************************/
Rook::Rook(const int &row, const int &col, const bool &whiteColor) 
   : Piece(row, col, whiteColor)
{
   pieceType = 'r';
   moveSet = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}