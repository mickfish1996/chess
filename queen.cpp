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

   std::vector<std::vector<int>> moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

   Position possPos = position;

   for (int i = 0; i < moveSet.size(); i++)
   {
      Position possPos = position;
      for (int col = 0; col < 8; col++)
      {
         // Adjusting possiblePosition to represent every position in captureSet.
         possPos.adjustRow(moveSet[i][0], 1);
         possPos.adjustCol(moveSet[i][1]);

         if (isValid(possPos.getRow()) && isValid(possPos.getCol()))
         {
            if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() == 's')
            {
               Move move;
               move.setSource(position);
               move.setDest(possPos);
               moves.insert(move);
            }

            if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() != 's' &&
               board.getPiece(possPos.getRow(), possPos.getCol()).isWhite() != isWhite())
            {
               Move move;
               move.setSource(position);
               move.setDest(possPos);
               move.setPieceType(board.getPiece(possPos.getRow(), possPos.getCol()).getType());
               moves.insert(move);

               //exit loop after a piece is encounterd
               break;
            }

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


