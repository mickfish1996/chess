/***********************************************************************
 * Source File:
 *     Board
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the board class. fill the board array with pieces and
 *     handle all movements in and out of the board.
 ************************************************************************/
#include "board.h"
#include "piece.h"
#include "space.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include <iostream>

/***************************************************************************
* DEFAULT CONSTRUCTOR
* The Default Constructor creates an empty board with only spaces.
***************************************************************************/
Board::Board()
{
   for (int row = 0; row < 8; row++)
   {
      for (int col = 0; col < 8; col++)
      {
         board[row][col] = new Space(row, col);
      }
   }
   currentTurn = 0;
}

///***************************************************************************
//* DEFAULT CONSTRUCTOR
//* The Default Constructor creates an empty board.
//***************************************************************************/
//Board::Board(bool build)
//{
//   for (int row = 2; row < 6; row++)
//   {
//      //std::vector<Piece> rowVector = {};
//
//      for (int col = 0; col < 8; col++)
//      {
//         board[row][col] = new Space(row, col);
//         //rowVector.push_back(emptySpace);
//      }
//
//      //board.push_back(rowVector);
//   }
//   fillBoard();
//   currentTurn = 0;
//}

/***************************************************************************
   fillBoard();
   currentTurn = 0;
}

/***************************************************************************
* GET PIECE
* Given a row and column, returns the piece at that location on the board.
***************************************************************************/
Piece Board::getPiece(const int& row, const int& col) const
{
   return *board[row][col];
}

/***************************************************************************
* ADD PIECE
* Given a piece, places that piece at the piece's location on the board.
***************************************************************************/
void Board::addPiece(Piece piece)
{
   int col = piece.getCol();
   int row = piece.getRow();

   *(board[row][col]) = piece;
}

/***************************************************************************
* FILL BOARD
* Fills the Board with the Default Pieces
***************************************************************************/
void Board::fillBoard()
{
   // Clears all the spaces on the board in rows 0,1,6,7.
   for (int i = 0; i < 8; i++)
   {
      delete board[0][i];
      delete board[1][i];
      delete board[6][i];
      delete board[7][i];
   }

   // Put kings on the board
   board[0][4] = new King(0, 4, true);
   board[7][3] = new King(7, 3, false);

   // put the rooks on the board
   board[0][0] = new Rook(0, 0, true);
   board[0][7] = new Rook(0, 7, true);
   board[7][0] = new Rook(7, 0, false);
   board[7][7] = new Rook(7, 7, false);

   // put the bishops on the board
   board[0][2] = new Bishop(0, 2, true);
   board[0][5] = new Bishop(0, 5, true);
   board[7][2] = new Bishop(7, 2, false);
   board[7][5] = new Bishop(7, 5, false);

   // put the queens on the board
   board[0][3] = new Queen(0, 3, true);
   board[7][4] = new Queen(7, 4, false);

   // Put the knight on the board
   board[0][1] = new Knight(0, 1, true);
   board[0][6] = new Knight(0, 6, true);
   board[7][1] = new Knight(7, 1, false);
   board[7][6] = new Knight(7, 6, false);

   // puts all the pawns on the board.
   for (int col = 0; col < 8; col++)
   {
      board[1][col] = new Pawn(1, col, true);
      board[6][col] = new Pawn(6, col, false);
   }
}

/*************************************
* Board ASCII Reference
* Top and Right sides are col and row.

* +---0-1-2-3-4-5-6-7---+
* |                     |
* 8                     7
* 7                     6
* 6                     5
* 5                     4
* 4                     3
* 3                     2
* 2                     1
* 1                     0
* |                     |
* +---a-b-c-d-e-f-g-h---+
*************************************/

/***************************************************************************
 * DRAW
 * Draws the board to the ogstream.
 ***************************************************************************/
void Board::draw(ogstream & gout) const
{
   for (int row = 0; row < 8; row++)
   {
      for (int col = 0; col < 8; col++)
         (*board[row][col]).draw(gout);
 
   }
}

/***************************************************************************
 * GET MOVES
 * This function is used to get around the splicing to the base class
 ***************************************************************************/
std::set<Move> Board::getMoves(int row, int col, Board& board) const
{
   return this->board[row][col]->getPossibleMoves(board);
}

/***************************************************************************
 * SWAP
 * This function is used to switch the pieces that are on the board.
 ***************************************************************************/
void Board::swap(const Move & move)
{
   increaseTurn();
   
   int rowFrom = move.getSource().getRow();
   int colFrom = move.getSource().getCol();

   int rowTo = move.getDest().getRow();
   int colTo = move.getDest().getCol();

   // Remove memory leak
   delete(board[rowTo][colTo]);

   int pawnColorMod = (board[rowFrom][colFrom]->isWhite() ? 1 : -1);

   // If the pawn is Being promoted it will upgrade the pawn to a Queen
   if (move.isPromotion())
   {
      board[rowTo][colTo] = new Queen(rowTo, colTo, move.isWhite());
   }

   // If the pawn moves two spaces this will update the EnPassant turn
   else if (board[rowFrom][colFrom]->getType() == 'p' && abs(rowFrom - rowTo) == 2)
   {
      updateNewPosition(rowFrom, colFrom, rowTo, colTo);
      board[rowTo][colTo]->setEnPassantTurn(currentTurn);
   }

   // If the pawn is going to enpassant, it moves to the space and sets the other pawn to space.
   else if(move.isEnpassant())
   {
      updateNewPosition(rowFrom, colFrom, rowTo, colTo);

      delete board[rowTo - pawnColorMod][colTo]; // Free memory at the pawn being removed.
      board[rowTo - pawnColorMod][colTo] = new Space(rowTo, colTo - pawnColorMod);
   }

   // If able to castle This function will determine the destination of the resultant pieces.
   else if (move.isCastle())
   {
      updateNewPosition(rowFrom, colFrom, rowTo, colTo);

      // This is used to determine where to put the rook after the king has moved.
      int rookOldCol;
      int rookKingDistance = 0;
      if ((colFrom - colTo) > 0)
      {
         rookKingDistance = 1;
         rookOldCol = 0;
      }
      else
      {
         rookKingDistance = -1;
         rookOldCol = 7;
      }
      
      int rookNewCol = colTo + rookKingDistance;

      // moves the rook into place
      delete board[rowTo][rookNewCol];                                // Deleting a Space
      updateNewPosition(rowFrom, rookOldCol, rowTo, rookNewCol);     // Updates new Rook
      board[rowFrom][rookOldCol] = new Space(rowFrom, rookOldCol);  // Sets Rook's old spot to Space
   }

   // Any other move is handled with this function.
   else
   {
      updateNewPosition(rowFrom, colFrom, rowTo, colTo);
   }

   // sets the space that the piece is coming from to a space.
   board[rowFrom][colFrom] = new Space(rowFrom, colFrom);  
}

void Board::updateNewPosition(const int rowFrom, const int colFrom, const int rowTo, const int colTo)
{
   board[rowTo][colTo] = board[rowFrom][colFrom];
   board[rowTo][colTo]->assignPosition(rowTo, colTo);
   board[rowTo][colTo]->incrementTurn();
}