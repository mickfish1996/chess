/***********************************************************************
 * Source File:
 *     Move
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Move class filling constructors and defining all
 *     methods including getSmith.
 ************************************************************************/
#include "move.h"

/***********************************************
* DEFAULT CONSTRUCTOR
* Establishes default attributes for Move().
***********************************************/
Move::Move()
{
   source = Position(); // Default Position
   dest = Position();
   pieceType = '0';    // Default of zero, for not specified.

   White = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castle = false;
}

/***********************************************
* NON-DEFAULT CONSTRUCTOR
* Establishes default parameters for Move()
* given a source Position.
***********************************************/
Move::Move(const Position& sourcePosition)
{
   source = sourcePosition;
   dest = Position();
   pieceType = ' ';                  // Default of space

   capture = false;
   White = false;
   enpassant = false;
   promotion = false;
   castle = false;
}

/***********************************************
 * Constructor
 * will recieve a string input and then assign 
 * that input to a move and destination.
 ***********************************************/
Move::Move(const std::string move)
{
   White = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castle = false;
   pieceType = ' ';

   const char* charMove = move.c_str();
   source = Position(charMove);
   dest = Position(charMove + 2);

   if (sizeof(move) == 5)
   {
      pieceType = charMove[5];
   }
}

/***********************************************
 * Constructor
 * Will recieve two location between 0 and 64
 * and will then assign them to source and 
 * destination.
 ***********************************************/
Move::Move(const int location1, const int location2)
{
   int row1 = location1 / 8;
   int col1 = location1 % 8;
   source = Position(row1, col1);

   int row2 = location2 / 8;
   int col2 = location2 % 8;
   dest = Position(row2, col2);
   pieceType = '0';
   White = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castle = false;
}

/***********************************************
 * GET SMITH
 * Will take the smith notations from the position
 * classes and append them together and if the
 * pieceType is not zero witll append the piece
 * to the char.
 ***********************************************/
std::string Move::getSmith() const
{
   if (pieceType == '0')
   {
      return source.getSmith() + dest.getSmith() + pieceType;
   }

   return source.getSmith() + dest.getSmith();
}

/***********************************************
 * operator==
 * used to see if two moves are equal to one
 * another.
 ***********************************************/
bool operator== (const Move& move1, const Move& move2)
{
   return (move1.source == move2.source &&
      move1.dest == move2.dest &&
      move1.pieceType == move2.pieceType &&
      move1.White == move2.White &&
      move1.capture == move2.capture &&
      move1.enpassant == move2.enpassant &&
      move1.promotion == move2.promotion &&
      move1.castle == move2.castle);
}