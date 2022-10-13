#include "piece.h"

/*********************************************************************
 * Piece
 * Default constructor will fill all values that are needed for the 
 * piece;
 *********************************************************************/
Piece::Piece()
{
   whiteColor = true;
   nMoves = 0;
   lastMove = Move();
   position = Position();
   pieceType = '0';
   enPassantTurn = 0;
}

/*********************************************************************
 * getPossibleMoves
 * Will return all the possible moves for the piece
 *********************************************************************/
std::set<Move> Piece::getPossibleMoves(const Board& board)
{
   std::set<Move> move;
   return move;
}

/*********************************************************************
 * assignPosition
 * Will take the char position given to the piece and will set the 
 * position based off of that.
 *********************************************************************/
void Piece::assignPosition(const char* position)
{
   int col;
   int row;
   if (position[0] == 'a')
      col = 0;
   else if (position[0] == 'b')
      col = 1;
   else if (position[0] == 'c')
      col = 2;
   else if (position[0] == 'd')
      col = 3;
   else if (position[0] == 'e')
      col = 4;
   else if (position[0] == 'f')
      col = 5;
   else if (position[0] == 'g')
      col = 6;
   else if (position[0] == 'h')
      col = 7;
   else
      col = 0;

   // subtract 49 because value is given in ascii value
   if (col != 0 && (0 <= position[1] <= 7))
      row = (int)position[1] - 49;
   else
   {
      row = 0;
      col = 0;
   }

   this->position.set(row, col);
}

void Piece::setEnPassantTurn(const Board& board)
{
   enPassantTurn = board.getCurrentTurn();
}

/*********************************************************************
 * Rook::Draw
 * Will draw the rook onto the screen
 *********************************************************************/
void Rook::draw(ogstream& gout) const
{
   gout.drawRook(position.getLocation(), isWhite());
}

/*********************************************************************
 * Rook::getPossibleMoves
 * Will get all the possible moves for the rook and return a set
 *********************************************************************/

std::set<Move> getPossibleMoves(Board & board)
{
   std::set<Move> moves;

   return moves;
}