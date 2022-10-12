#include "board.h"
#include "piece.h"
#include "space.h"
#include <iostream>

/***************************************************************************
* DEFAULT CONSTRUCTOR
* The Default Constructor creates an empty board.
***************************************************************************/
Board::Board()
{
   for (int row = 0; row < 8; row++)
   {
      std::vector<Piece> rowVector = {};

      for (int col = 0; col < 8; col++)
      {
         Space emptySpace(row, col);
         rowVector.push_back(emptySpace);
      }

      board.push_back(rowVector);
   }
}

/***************************************************************************
* GET PIECE
* Given a row and column, returns the piece at that location on the board.
***************************************************************************/
Piece Board::getPiece(const int& row, const int& col) const
{
   //return *(this->board[row][col]);
   return board[row][col];
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

   board[row][col] = piece;
}