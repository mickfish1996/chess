#include "board.h"
#include "piece.h"
#include "space.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include <iostream>

/***************************************************************************
* DEFAULT CONSTRUCTOR
* The Default Constructor creates an empty board.
***************************************************************************/
Board::Board()
{
   for (int row = 0; row < 8; row++)
   {
      //std::vector<Piece> rowVector = {};

      for (int col = 0; col < 8; col++)
      {
         board[row][col] = new Space(row, col);
         //rowVector.push_back(emptySpace);
      }

      //board.push_back(rowVector);
   }
      currentTurn = 0;
}

/***************************************************************************
* DEFAULT CONSTRUCTOR
* The Default Constructor creates an empty board.
***************************************************************************/
Board::Board(bool build)
{
   for (int row = 0; row < 8; row++)
   {
      //std::vector<Piece> rowVector = {};

      for (int col = 0; col < 8; col++)
      {
         board[row][col] = new Space(row, col);
         //rowVector.push_back(emptySpace);
      }

      //board.push_back(rowVector);
   }
   fillBoard();
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
* add Piece
* Given a row and column, places the piece at that location on the board.
***************************************************************************/
void Board::addPiece(Piece piece)
{
   int col = piece.getCol();
   int row = piece.getRow();

   board[row][col] = &piece;
}

/***************************************************************************
* fill Board
* will add all pieces to the board
***************************************************************************/
void Board::fillBoard()
{
   //delete board[0][4];
   board[0][4] = new King(0, 4, true);
   board[7][3] = new King(7, 3, false);

   board[0][0] = new Rook(0, 0, true);
   board[0][7] = new Rook(0, 7, true);
   board[7][0] = new Rook(7, 0, false);
   board[7][7] = new Rook(7, 7, false);

   board[0][2] = new Bishop(0, 2, true);
   board[0][5] = new Bishop(0, 5, true);
   board[7][2] = new Bishop(7, 2, false);
   board[7][5] = new Bishop(7, 5, false);

   board[0][3] = new Queen(0, 3, true);
   board[7][4] = new Queen(7, 4, false);

   board[0][1] = new Knight(0, 1, true);
   board[0][6] = new Knight(0, 6, true);
   board[7][1] = new Knight(7, 1, false);
   board[7][6] = new Knight(7, 6, false);

   for (int col = 0; col < 8; col++)
   {
      board[1][col] = new Pawn(1, col, true);
      board[6][col] = new Pawn(6, col, false);
   }


   

}

/***************************************************************************
 * King
 * will set all the values to the defaults because there were no inputs
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
 * getMoves
 * This function is used to get around the splicing to the base class
 ***************************************************************************/
std::set<Move> Board::setMoves(int row, int col, Board& board) const
{
   return this->board[row][col]->getPossibleMoves(board);
}

/***************************************************************************
 * Swap
 * This function is used to switch the pieces that are on the board.
 ***************************************************************************/
void Board::swap(const int posTo, const int posFrom)
{
   increaseTurn();
   

   int rowFrom = posFrom / 8;
   int colFrom = posFrom % 8;

   int rowTo = posTo / 8;
   int colTo = posTo % 8;

   int next = (board[rowFrom][colFrom]->isWhite() ? 1 : -1);

   // This handles the promotion of the white pawn
   if (board[rowFrom][colFrom]->getType() == 'p' &&
      board[rowFrom][colFrom]->isWhite() && posTo / 8 == 7)
   {
      board[rowTo][colTo] = new Queen(posTo / 8, posTo % 8, true);
   }

   // This handles the promotion of the black pawn
   else if (board[rowFrom][colFrom]->getType() == 'p' &&
      !board[rowFrom][colFrom]->isWhite() && posTo / 8 == 0)
   {
      board[rowTo][colTo] = new Queen(posTo / 8, posTo % 8, false);
   }

   // If the pawn moves two spaces this will update the EnPassant turn
   else if (board[rowFrom][colFrom % 8]->getType() == 'p' && abs(rowFrom - rowTo) == 2)
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();
      board[rowTo][colTo]->setEnPassantTurn(currentTurn);
   }

   // In order to see if the piece can En Passant
   else if (board[rowFrom][colFrom]->getType() == 'p' &&
      board[rowTo][colTo]->getType() == 's' &&
      board[rowTo - next][colTo]->getType() == 'p' &&
      board[rowTo - next][colTo]->isWhite() != board[rowFrom][colFrom]->isWhite())
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();
      board[rowTo - next][colTo] = new Space(rowTo, colTo - next);
   }


   else
   {
      board[rowTo][colTo] = board[rowFrom][colFrom];
      board[rowTo][colTo]->assignPosition(rowTo, colTo);
      board[rowTo][colTo]->setTurn();
   }

   board[rowFrom][colFrom] = new Space(rowFrom, colFrom);  

}