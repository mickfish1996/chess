#include "pawn.h"
#include <vector>

Pawn::Pawn()
{
   position = Position();
   whiteColor = true;
   lastMove = Move();
   nMoves = 0;
   enPassantTurn = 0;
   pieceType = 'p';
}

// TODO: Add sets for white and black pawns separately, or auto convert
// white to black.   ///////////////////////////////////////////////////////
// TODO: Check to make sure that we are checking for valid ranges in getPossibleMoves.
std::set<Move> Pawn::getPossibleMoves(const Board& board)
{
   // moveSet and captureSet are vectors in format of 
   // { {adjustRow, adjustCol} }.
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
      possPos.adjustRow(moveSet[i][0]);
      possPos.adjustCol(moveSet[i][1]);
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
         if (possPos.getRow() == 7)
         {
            move.setPromotion(true);
         }

         possibleMoves.insert(move);
      }
   }

   // Go through all possible moves in captureSet.
   for (int i = 0; i < size(captureSet); i++)
   {
      Position possPos = position;

      // Adjusting possiblePosition to represent every position in captureSet.
      possPos.adjustRow(captureSet[i][0]);
      possPos.adjustCol(captureSet[i][1]);
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

   // Check for En Passant
   for (int i = 0; i < size(enPassantSet); i++)
   {
      Position possPos = position;

      // Adjusting possiblePosition to represent every position in enPassantSet.
      possPos.adjustRow(enPassantSet[i][0]);
      possPos.adjustCol(enPassantSet[i][1]);
      Piece possPiece = board.getPiece(possPos.getRow(), possPos.getCol());

      // If possPiece is a pawn, and possPiece just moved two spaces, then make a move.
      if (possPiece.getType() == 'p' && possPiece.getNMoves() == 1)
      {
         if (possPiece.getEnPassantTurn() == board.getCurrentTurn() - 1)
         {
            Move move = Move();
            move.setSource(this->getPosition());
            possPos.adjustRow(moveSet[0][0]);   // Auto adjust for when change moveSet for Black Pieces.n
            move.setDest(possPos);
            move.setPieceType(this->getType());
            move.setWhiteColor(this->isWhite());
            move.setEnPassant(true);
            possibleMoves.insert(move);
         }
      }
   }

   return possibleMoves;
}