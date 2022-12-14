/***********************************************************************
 * Source File:
 *     Pawn
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Pawn class filling constructors and defining all
 *     methods including getPossibleMoves
 ************************************************************************/
#include "pawn.h"
#include <vector>

/***************************************************************************
 * DEFAULT CONSTRUCTOR
 * will set all values to a default value
 ***************************************************************************/
Pawn::Pawn() : Piece()
{
   pieceType = 'p';
}

/***************************************************************************
 * CONSTRUCTOR
 * Given the row, col, and boolean color, this constructor will set the 
 * position and the color of the pawn.
 ***************************************************************************/
Pawn::Pawn(const int &row, const int &col, const bool &whiteColor)
   : Piece(row, col, whiteColor)
{
   pieceType = 'p';
}

/***************************************************************************
 * GET POSSIBLE MOVES
 * Used to get all the places that the pawn is able to move on the board.
 ***************************************************************************/
std::set<Move> Pawn::getPossibleMoves(const Board& board)
{
   // moveSet and captureSet are vectors in format of 
   // { {adjustRow, adjustCol} }.

   int whiteMultiplier = (whiteColor ? 1 : -1);
   std::vector<std::vector<int>> captureSet = { {1, -1}, {1, 1} };
   std::vector<std::vector<int>> enPassantSet = { {0, -1}, {0, 1} };
   std::vector<std::vector<int>> moveSet;
   if (nMoves != 0)
   {
      moveSet = { {1, 0} };
   }
   else
   {
      moveSet = { {1, 0}, {2, 0} };
   }

   std::set<Move> possibleMoves = { };

   // Go through all possible moves in moveSet.
   for (int i = 0; i < size(moveSet); i++)
   {
      Position possPos = position;

      // Adjusting possiblePosition to represent every position in moveSet.
      possPos.adjustRow(moveSet[i][0] * whiteMultiplier);
      possPos.adjustCol(moveSet[i][1]);
      if (possPos.isValid())
      {
         Piece possPiece = board.getPiece(possPos.getRow(), possPos.getCol());

         // If the destination piece is a Space, add possible move.
         if (possPiece.getType() == 's')
         {
            Move move = Move();
            move.setSource(this->getPosition());
            move.setDest(possPos);
            move.setPieceType(this->getType());
            move.setWhiteColor(this->isWhite());

            // Check for Promotion
            if (possPos.getRow() == 7 || possPos.getRow() == 0)
            {
               move.setPromotion(true);
            }

            possibleMoves.insert(move);
         }
      }
   }

   // Go through all possible moves in captureSet.
   for (int i = 0; i < size(captureSet); i++)
   {
      Position possPos = position;

      // Adjusting possiblePosition to represent every position in captureSet.
      possPos.adjustRow(captureSet[i][0] * whiteMultiplier);
      possPos.adjustCol(captureSet[i][1]);
      if (possPos.isValid())
      {
         Piece possPiece = board.getPiece(possPos.getRow(), possPos.getCol());

         // If the destination piece is not a space and is of the opposite color, add capture.
         if (possPiece.getType() != 's' && possPiece.isWhite() != this->isWhite())
         {
            Move move = Move();
            move.setSource(this->getPosition());
            move.setDest(possPos);
            move.setPieceType(this->getType());
            move.setWhiteColor(this->isWhite());
            move.setCapture(true);
            possibleMoves.insert(move);
         }
      }
   }

   // Check for En Passant
   for (int i = 0; i < size(enPassantSet); i++)
   {
      Position possPos = position;

      // Adjusting possiblePosition to represent every position in enPassantSet.
      // No need to adjust row, since enPassantSet[i][0] is 0.
      possPos.adjustCol(enPassantSet[i][1]);
      if (possPos.isValid())
      {
         Piece possPiece = board.getPiece(possPos.getRow(), possPos.getCol());

         // If possPiece is a pawn, and possPiece just moved two spaces, then make a move.
         if (possPiece.getType() == 'p' && possPiece.getNMoves() == 1)     // && of opposite type?
         {
            if (possPiece.getEnPassantTurn() == board.getCurrentTurn()) //
            {
               Move move = Move();
               move.setSource(this->getPosition());
               possPos.adjustRow(moveSet[0][0] * whiteMultiplier);   // Auto adjust for when change moveSet for Black Pieces.
               move.setDest(possPos);
               move.setPieceType(this->getType());
               move.setWhiteColor(this->isWhite());
               move.setEnPassant(true);
               possibleMoves.insert(move);
            }
         }
      }
   }

   return possibleMoves;
}