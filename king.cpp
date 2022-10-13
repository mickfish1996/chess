#include "king.h"

/***************************************************************************
 * King
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
King::King()
{
   position = Position();
   whiteColor = true;
   lastMove = Move();
   nMoves = 0;
   pieceType = 'k';
   /*const char pieceType = 'k';*/
}

/***************************************************************************
 * King
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
King::King(int row, int col, bool white)
{
   position = Position(row, col);
   lastMove = Move();
   nMoves = 0;
   whiteColor = white;
   pieceType = 'k';
}

/***************************************************************************
* getPossibleMoves
* Will return a set with all possible moves for the king class.
***************************************************************************/
std::set<Move> King::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   // Possible castleing moves.
   if (nMoves == 0)
   {
      // Position in the board of what should be a space
      int posSpaceRow = position.getRow();
      int posSpaceCol = 5;

      // Position in the board that should be a possible move
      int posMoveRow = position.getRow();
      int posMoveCol = 6;

      // Position in the board that should be a rook.
      int posRookRow = position.getRow();
      int posRookCol = 7;

      if (board.getPiece(posMoveRow, posMoveCol).getType() == 's' &&
         board.getPiece(posSpaceRow, posSpaceCol).getType() == 's' &&
         board.getPiece(posRookRow, posRookCol).getType() == 'r' &&
         board.getPiece(posRookRow, posRookCol).getNMoves() == 0)
      {
         Move move;
         move.setSource(getPosition());
         move.setDest(Position(posMoveRow, posMoveCol));
         move.setCastleK(true);
         move.setPieceType('c');
         moves.insert(move);
      }
   }

   // Possible Queen side castling moves
   if (nMoves == 0)
   {
      // Position in the board of what should be a space
      int posSpaceRow1 = position.getRow();
      int posSpaceCol1 = 3;

      // Position in the board that should be a possible move
      int posMoveRow = position.getRow();
      int posMoveCol = 2;

      // Position in the board of what should be a space
      int posSpaceRow2 = position.getRow();
      int posSpaceCol2 = 1;

      // Position in the board that should be a rook.
      int posRookRow = position.getRow();
      int posRookCol = 0;

      if (board.getPiece(posMoveRow, posMoveCol).getType() == 's' &&
         board.getPiece(posSpaceRow1, posSpaceCol1).getType() == 's' &&
         board.getPiece(posSpaceRow2, posSpaceCol2).getType() == 's' &&
         board.getPiece(posRookRow, posRookCol).getType() == 'r' &&
         board.getPiece(posRookRow, posRookCol).getNMoves() == 0)
      {
         Move move;
         move.setSource(getPosition());
         move.setDest(Position(posMoveRow, posMoveCol));
         move.setCastleQ(true);
         move.setPieceType('c');
         moves.insert(move);
      }
   }

   for (int row = position.getRow() - 1; row <= position.getRow() + 1; row++)
   {
      for (int col = position.getCol() - 1; col <= position.getCol() + 1; col++)
      {
         if (isValid(row) && isValid(col))
         {
            if (board.getPiece(row, col).getType() == 's') //Kyler commented out
            {
               Move move;
               move.setSource(getPosition());
               move.setDest(Position(row, col));
               moves.insert(move);

            }

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

   int size = moves.size();
   return moves;
}

/***************************************************************************
 * isValid
 * will confirm that all positions are in a valid spot to move.
 ***************************************************************************/
bool King::isValid(const int num)
{
   if (num < 0 || num > 7)
      return false;
   return true;
}
