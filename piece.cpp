/***********************************************************************
 * Source File:
 *     Piece, Rook
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the Piece and rook class's filling constructors and 
 *     defining all methods including getPossibleMoves
 ************************************************************************/
#include "piece.h"

/*********************************************************************
 * DEFAULT CONSTRUCTOR
 * Default constructor will fill all values that are needed for the 
 * piece.
 *********************************************************************/
Piece::Piece()
{
   whiteColor = true;
   nMoves = 0;
   lastMove = Move();
   position = Position();
   enPassantTurn = 0;
   pieceType = '0';
   moveSet = { };
}

/*********************************************************************
 * NON-DEFAULT CONSTRUCTOR
 * The Non-Default Constructor will copy the parameters into the piece.
 *********************************************************************/
Piece::Piece(const int row, const int col, const bool whiteColor)
{
   this->whiteColor = whiteColor;
   nMoves = 0;
   lastMove = Move();
   position = Position(row, col);
   enPassantTurn = 0;
   pieceType = '0';
   moveSet = { };
}

/*********************************************************************
 * GET POSSIBLE MOVES
 * Will return all the possible moves for the piece
 *********************************************************************/
std::set<Move> Piece::getPossibleMoves(const Board& board)
{
   std::set<Move> moves;

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

/*********************************************************************
 * ASSIGN POSITION
 * Will take the char position given to the piece and will set the 
 * position based off of that.
 *********************************************************************/
void Piece::assignPosition(const char* position)
{
   int col;
   int row;
   if (position[0] == 'a')
      col = 0;
   else if (position[0] == 'b')
      col = 1;
   else if (position[0] == 'c')
      col = 2;
   else if (position[0] == 'd')
      col = 3;
   else if (position[0] == 'e')
      col = 4;
   else if (position[0] == 'f')
      col = 5;
   else if (position[0] == 'g')
      col = 6;
   else if (position[0] == 'h')
      col = 7;
   else
      col = 0;

   // subtract 49 because value is given in ascii value
   if (col != 0 && (0 <= position[1] <= 7))
      row = (int)position[1] - 49;
   else
   {
      row = 0;
      col = 0;
   }

   this->position.set(row, col);
}

/*********************************************************************
 * SET ENPASSANT TURN
 * Will take the integer value that was passed and set enpassantTurn
 * to the turn number that was sent in.
 *********************************************************************/
void Piece::setEnPassantTurn(const int& turn)
{
   enPassantTurn = turn;
}