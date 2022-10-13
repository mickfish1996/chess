#include "board.h"
#include "piece.h"
#include "space.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
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
   board[0][4] = new King(0, 4, false);
   board[7][3] = new King(7, 3, true);

   board[0][0] = new Rook(0, 0, false);
   board[0][7] = new Rook(0, 7, false);
   board[7][0] = new Rook(7, 0, true);
   board[7][7] = new Rook(7, 7, true);

   board[0][2] = new Bishop(0, 2, false);
   board[0][5] = new Bishop(0, 5, false);
   board[7][2] = new Bishop(7, 2, true);
   board[7][5] = new Bishop(7, 5, true);

   board[0][3] = new Queen(0, 3, false);
   board[7][4] = new Queen(7, 4, true);

   for (int col = 0; col < 8; col++)
   {
      board[1][col] = new Pawn(1, col, false);
      board[6][col] = new Pawn(6, col, true);
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

   board[posTo / 8][posTo % 8] = board[posFrom / 8][posFrom % 8];
   board[posTo / 8][posTo % 8]->assignPosition(posTo / 8, posTo % 8);
   board[posTo / 8][posTo % 8]->setTurn();


   board[posFrom / 8][posFrom % 8] = new Space(posFrom / 8, posFrom % 8);

   

}