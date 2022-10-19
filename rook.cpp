#include "rook.h"

/*********************************************************************
 * Rook:: Default Constructor
 * Will set all vaues to a default value.
 *********************************************************************/
Rook::Rook() : Piece()
{
   pieceType = 'r';
}

/*********************************************************************
 * Rook Constructor
 * Will set all vaues to a default value. and will set the position
 * and the color of the piece
 *********************************************************************/
Rook::Rook(const int &row, const int &col, const bool &whiteColor) 
   : Piece(row, col, whiteColor)
{
   pieceType = 'r';
}

/*********************************************************************
 * Rook::Draw
 * Will draw the rook onto the screen
 *********************************************************************/
void Rook::draw(ogstream& gout) const
{
   gout.drawRook(position.getLocation(), !isWhite());
}

/*********************************************************************
 * Rook::getPossibleMoves
 * Will get all the possible moves for the rook and return a set
 *********************************************************************/

std::set<Move> Rook::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

   // A vector of all possible changes that the rook can make.
   std::vector<std::vector<int>> moveSet = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

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

/*********************************************************************
 * Rook:: isValid
 * Will check to ensure the number given is between 0 and 8.
 *********************************************************************/
bool Rook::isValid(const int& num)
{
   if (num < 0 || num > 7)
      return false;
   return true;
}