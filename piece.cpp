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
 * Piece
 * Default constructor will fill all values that are needed for the 
 * piece;
 *********************************************************************/
Piece::Piece()
{
   whiteColor = true;
   nMoves = 0;
   lastMove = Move();
   position = Position();
   pieceType = '0';
   enPassantTurn = 0;
}

/*********************************************************************
 * getPossibleMoves
 * Will return all the possible moves for the piece
 *********************************************************************/
std::set<Move> Piece::getPossibleMoves(const Board& board)
{
   std::set<Move> move;
   return move;
}

/*********************************************************************
 * assignPosition
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
 * setEnpassantTurn
 * Will take the integer value that was passed and set enpassantTurn
 * to the turn number that was sent in.
 *********************************************************************/
void Piece::setEnPassantTurn(const int& turn)
{
   enPassantTurn = board.getCurrentTurn();
}

/*********************************************************************
 * Rook:: Default Constructor
 * Will set all vaues to a default value.
 *********************************************************************/
Rook::Rook()
{
   position = Position();
   whiteColor = true;
   lastMove = Move();
   nMoves = 0;
   enPassantTurn = 0;
   pieceType = 'r';
}

/*********************************************************************
 * Rook:: Constructor
 * Will set all vaues to a default value. and will set the position
 * and the color of the piece
 *********************************************************************/
Rook::Rook(int row, int col, bool white)
{
   position = Position(row, col);
   whiteColor = white;
   lastMove = Move();
   nMoves = 0;
   enPassantTurn = 0;
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

std::set<Move> Rook::getPossibleMoves(const Board & board)
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