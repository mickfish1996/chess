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
 * Queen
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
Queen::Queen()
{
   position = Position();
   whiteColor = true;
   lastMove = Move();
   nMoves = 0;
   pieceType = 'q';
}

/***************************************************************************
 * Queen
 * will set all the values to the included variables
 ***************************************************************************/
Queen::Queen(int row, int col, bool white)
{
   position = Position(row, col);
   whiteColor = white;
   lastMove = Move();
   nMoves = 0;
   pieceType = 'q';
}

/***************************************************************************
 * Queen
 * will return all of the possible moves for the board
 ***************************************************************************/
std::set<Move> Queen::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   // A vector of all possible movement vectors.
   std::vector<std::vector<int>> moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

   // Position used for finding all possible moves.
   Position possPos = position;

   // will go through all changes.
   for (int i = 0; i < moveSet.size(); i++)
   {
      // changable position used for finding positions on the board.
      Position possPos = position;

      // Because the piece can slide the loop is to see all spots on the board
      // that are possible.
      for (int col = 0; col < 8; col++)
      {
         // Adjusting possiblePosition to represent every position in captureSet.
         possPos.adjustRow(moveSet[i][0], 1);
         possPos.adjustCol(moveSet[i][1]);

         // Checks for valid row and col.
         if (isValid(possPos.getRow()) && isValid(possPos.getCol()))
         {
            // checks if the spot is empty
            if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() == 's')
            {
               Move move;
               move.setSource(position);
               move.setDest(possPos);
               moves.insert(move);
            }

            // checks what kind of piece it is hitting and if it is the same color.
            if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() != 's' &&
               board.getPiece(possPos.getRow(), possPos.getCol()).isWhite() != isWhite())
            {
               Move move;
               move.setSource(position);
               move.setDest(possPos);
               move.setPieceType(board.getPiece(possPos.getRow(), possPos.getCol()).getType());
               moves.insert(move);

               //exit loop after a piece is encountered
               // TODO: Make the loop so that break is not needed.
               break;
            }

            // if a piece of the same color is hit it cannot go any further.
            else if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() != 's' &&
               board.getPiece(possPos.getRow(), possPos.getCol()).isWhite() == isWhite())
               break;
         }
      }
   }

   return moves;
}

/***************************************************************************
 * Queen
 * will determine if a number is in range of the board
 ***************************************************************************/
bool Queen::isValid(const int num)
{
   if (num < 0 || num > 7)
      return false;
   return true;
}