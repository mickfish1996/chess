
/***********************************************************************
 * Source File:
 *     Bishop
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the bishop piece so that it can be seen and moved 
 *     across the board..
 ************************************************************************/
#include "bishop.h"

/***************************************************************************
 * Bishop
 * will set all the values to the defaults because there were no inputs
 ***************************************************************************/
Bishop::Bishop() : Piece()
{
   pieceType = 'b';
}

/***************************************************************************
 * King
 * will set all the values to the included variables
 ***************************************************************************/
Bishop::Bishop(const int &row, const int &col, const bool &whiteColor) 
   : Piece(row, col, whiteColor)
{
   pieceType = 'b';
}

/***************************************************************************
 * King
 * will return all of the possible moves for the board
 ***************************************************************************/
std::set<Move> Bishop::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   std::vector<std::vector<int>> moveSet = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };

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
         if (possPos.isValid())
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

               //exit loop after a piece is encounterd
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