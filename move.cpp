/******************************************************************************
 * MOVE
 * Contains all information regarding moves. Helps with Piece.getPossibleMoves
 * functions.
******************************************************************************/
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

   isWhite = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castleK = false;
   castleQ = false;
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
   isWhite = false;
   enpassant = false;
   promotion = false;
   castleK = false;
   castleQ = false;
}

/***********************************************
 *
 ***********************************************/
Move::Move(const std::string move)
{
   isWhite = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castleK = false;
   castleQ = false;
   pieceType = ' ';

   const char* charMove = move.c_str();
   source = Position(charMove);
   dest = Position(charMove + 2);

   if (sizeof(move) == 5)
   {
      pieceType = charMove[5];
   }
}

Move::Move(const int location1, const int location2)
{
   int row1 = location1 / 8;
   int col1 = location1 % 8;
   source = Position(row1, col1);

   int row2 = location2 / 8;
   int col2 = location2 % 8;
   dest = Position(row2, col2);
   pieceType = '0';
   isWhite = false;
   capture = false;
   enpassant = false;
   promotion = false;
   castleK = false;
   castleQ = false;
}
/***********************************************
 *
 ***********************************************/
std::string Move::getSmith() const
{
   if (pieceType == '0')
   {
      return source.getSmith() + dest.getSmith() + pieceType;
   }

   return source.getSmith() + dest.getSmith();
}

bool operator== (const Move& move1, const Move& move2)
{
   return (move1.source == move2.source &&
      move1.dest == move2.dest &&
      move1.pieceType == move2.pieceType &&
      move1.isWhite == move2.isWhite &&
      move1.capture == move2.capture &&
      move1.enpassant == move2.enpassant &&
      move1.promotion == move2.promotion &&
      move1.castleK == move2.castleK &&
      move1.castleQ == move2.castleQ);
}