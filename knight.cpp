/***********************************************************************
 * Source File:
 *     Knight
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Knight class filling constructors and getPossibleMoves
 *     along with all other methods not able to fit in the header file.
 ************************************************************************/
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

   // A vecot filled with all of the possible spots from the current space
   // that the piece can move to.
   std::vector<std::vector<int>> moveSet = { {2, -1}, {1, -2}, {2, 1},{1, 2}, {-1, 2}, {-2, -1}, {-1, -2}, {-2, 1} };
   
   Position possPos = position;

   // since there are only 8 possible spots and a knight cannot slide this loop is used
   for (int i = 0; i < moveSet.size(); i++)
   {
      // changleble position to determine where the knight can move.
      Position possPos;
      
      // Adjusting possiblePosition to represent every position in captureSet.
      possPos.adjustRow(moveSet[i][0], 1);
      possPos.adjustCol(moveSet[i][1]);

      // Checks for all valid movemeints on the board.
      if (isValid(possPos.getRow()) && isValid(possPos.getCol()))
      { 
         // Checks to see if the spot is empty.
         if (board.getPiece(possPos.getRow(), possPos.getCol()).getType() == 's')
         {
            Move move;
            move.setSource(position);
            move.setDest(possPos);
            moves.insert(move);
         }

         // Checks to see what piece type is in the spot and what color it is.
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

   // Returns the final set of Moves.
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