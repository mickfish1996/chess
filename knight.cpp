#include "knight.h"

/***************************************************************************
 * Knight
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
Knight::Knight()
{
   position = Position();
   whiteColor = true;
   lastMove = Move();
   nMoves = 0;
   pieceType = 'k';
}

/***************************************************************************
 * Knight
 * will set all the values to the included variables
 ***************************************************************************/
Knight::Knight(int row, int col, bool white)
{
   position = Position(row, col);
   whiteColor = white;
   lastMove = Move();
   nMoves = 0;
   pieceType = 'k';
}

/***************************************************************************
 * Knight
 * will return all of the possible moves for the board
 ***************************************************************************/
std::set<Move> Knight::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   std::vector<std::vector<int>> moveSet = { {2, -1}, {1, -2}, {2, 1},{1, 2}, {-1, 2}, {-2, -1}, {-1, -2}, {-2, 1} };
   
   Position possPos = position;

   for (int i = 0; i < moveSet.size(); i++)
   {
      Position possPos = position;
      
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
            }          
         }      
   }
   return moves;
}

/***************************************************************************
 * Knight
 * will determine if a number is in range of the board
 ***************************************************************************/
bool Knight::isValid(const int num)
{
   if (num < 0 || num > 7)
      return false;
   return true;
}