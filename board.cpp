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
      //std::vector<Piece> rowVector = {};

      for (int col = 0; col < 8; col++)
      {
         board[row][col] = new Space(row, col);
      }
   }
      currentTurn = 0;
}

/***************************************************************************
* GET PIECE
* Given a row and column, returns the piece at that location on the board.
***************************************************************************/
Piece Board::getPiece(const int& row, const int& col) const
{
   //return *(this->board[row][col]);
   return *board[row][col];
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
* ADD Piece
* Given a piece, places that piece at the piece's location on the board.
***************************************************************************/
void Board::addPiece(Piece piece)
{
   int col = piece.getCol();
   int row = piece.getRow();
   
   board[row][col] = &piece;
}

/***************************************************************************
* FILL BOARD
* Fills the board with the default pieces.
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

   int next = (board[rowFrom][colFrom]->isWhite() ? 1 : -1);

   // If the pawn is Being promoted it will upgrade the pawn to a Queen
   if (move.isPromotion())
   {
      board[rowTo][colTo] = new Queen(rowTo, colTo, move.isWhite());
   }

   // If the pawn moves two spaces this will update the EnPassant turn
   else if (board[rowFrom][colFrom % 8]->getType() == 'p' && abs(rowFrom - rowTo) == 2)
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();
      board[rowTo][colTo]->setEnPassantTurn(currentTurn);
   }

   // The pawn is able to enpassant, it moves to the space and sets the other pawn to space.
   else if(move.isEnpassant())
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();

      delete board[rowTo - next][colTo]; // Free memory at the pawn being removed.
      board[rowTo - next][colTo] = new Space(rowTo, colTo - next);
   }

   // If able to castle This function will determine the destination of the resultant pieces.
   else if (move.isCastle())
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();

      // This is used to determine where to put the rook after the king has moved.
      int col;
      if ((colFrom - colTo) > 0)
      {
         next = 1;
         col = 0;
      }
      else
      {
         next = -1;
         col = 7;
      }
         
      // moves the rook into place
      delete board[rowTo][colTo + next];
      board[rowTo][colTo + next] = board[rowFrom][col];
      board[rowTo][colTo + next]->assignPosition(rowTo, colTo + next);
      board[rowTo][colTo + next]->setTurn();

      board[rowFrom][col] = new Space(rowFrom, col);

   }

   // Any other move is handled with this function.
   else
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();
   }

   // sets the space that the piece is coming from to a space.

   //delete(board[rowFrom][colFrom]);
   board[rowFrom][colFrom] = new Space(rowFrom, colFrom);  

}