/***********************************************************************
 * Source File:
 *     King
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the King class filling constructors and getPossibleMoves
 *     along with all other methods not able to fit in the header file.
 ************************************************************************/
#include "king.h"

/***************************************************************************
 * DEFAULT CONSTRUCTOR
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
King::King() : Piece()
{
   pieceType = 'k';
}

/***************************************************************************
 * CONSTRUCTOR
 * will set all the values to the values that have been recieved.
 ***************************************************************************/
King::King(const int &row, const int &col, const bool &whiteColor)
   : Piece(row, col, whiteColor)
{
   pieceType = 'k';
}

/***************************************************************************
* GET POSSIBLE MOVES
* Will return a set with all possible moves for the king class.
***************************************************************************/
std::set<Move> King::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   // This variable is to help with determining if black or white pieces
   // are able to castle.
   int next = (isWhite() ? 1 : -1);

   // Possible castleing moves.
   if (nMoves == 0)
   {
      // Position in the board of what should be a space
      int posSpaceRow = position.getRow();
      int posSpaceCol = position.getCol() + (next);

      // Position in the board that should be a possible move
      int posMoveRow = position.getRow();
      int posMoveCol = position.getCol() + (2 * next);

      // Position in the board that should be a rook.
      int posRookRow = position.getRow();
      int posRookCol = position.getCol() + (3 * next);

      // Sees if all necassary requirments to castle are met. then fills the 
      // move with all relevant data.
      if (board.getPiece(posMoveRow, posMoveCol).getType() == 's' &&
         board.getPiece(posSpaceRow, posSpaceCol).getType() == 's' &&
         board.getPiece(posRookRow, posRookCol).getType() == 'r' &&
         board.getPiece(posRookRow, posRookCol).getNMoves() == 0)
      {
         Move move;
         move.setSource(getPosition());
         move.setDest(Position(posMoveRow, posMoveCol));
         move.setCastle(true);
         move.setPieceType('c');
         moves.insert(move);
      }
   }

   // Possible Queen side castling moves
   if (nMoves == 0)
   {
      // Position in the board of what should be a space
      int posSpaceRow1 = position.getRow();
      int posSpaceCol1 = position.getCol() - next;

      // Position in the board that should be a possible move
      int posMoveRow = position.getRow();
      int posMoveCol = position.getCol() - (2 * next);

      // Position in the board of what should be a space
      int posSpaceRow2 = position.getRow();
      int posSpaceCol2 = position.getCol() - ( 3 * next);

      // Position in the board that should be a rook.
      int posRookRow = position.getRow();
      int posRookCol = position.getCol() - (4 * next);

      // Sees if all necassary requirments to castle are met. then fills the 
      // move with all relevant data.
      if (board.getPiece(posMoveRow, posMoveCol).getType() == 's' &&
         board.getPiece(posSpaceRow1, posSpaceCol1).getType() == 's' &&
         board.getPiece(posSpaceRow2, posSpaceCol2).getType() == 's' &&
         board.getPiece(posRookRow, posRookCol).getType() == 'r' &&
         board.getPiece(posRookRow, posRookCol).getNMoves() == 0)
      {
         Move move;
         move.setSource(getPosition());
         move.setDest(Position(posMoveRow, posMoveCol));
         move.setCastle(true);
         move.setPieceType('c');
         moves.insert(move);
      }
   }

   // Will go through all the valid spots around th king to see if it is able to move to 
   // one of those spaces.
   for (int row = position.getRow() - 1; row <= position.getRow() + 1; row++)
   {
      for (int col = position.getCol() - 1; col <= position.getCol() + 1; col++)
      {
         // checks if the possible spot is a valid space on the board.
         if (Position(row, col).isValid())
         {
            // Sees if the spot is just a space
            if (board.getPiece(row, col).getType() == 's')
            {
               Move move;
               move.setSource(getPosition());
               move.setDest(Position(row, col));
               moves.insert(move);
            }

            // Sees what color the adjacent piece is and what type it is.
            else if (isWhite() != board.getPiece(row, col).isWhite())
            {
               Move move;
               move.setSource(getPosition());
               move.setDest(Position(row, col));
               move.setPieceType(board.getPiece(row, col).getType());
               moves.insert(move);
            }
         }
      }
   }
   // returns the final set of moves that was generated.
   return moves;
}