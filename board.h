/***********************************************************************
 * Header File:
 *     Board
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     Defines class used to hold all the pieces and move those pieces.
 ************************************************************************/
#pragma once
#include <vector>
#include <iostream>
#include "uiDraw.h"
#include "piece.h"

class Piece;

/******************************************************************************
* BOARD
* The Board class handles all Board operations including drawing and moving
* pieces.
******************************************************************************/
class Board
{
public:
   Board();
   
   // Geters
   Piece getPiece(const int& row, const int& col) const;
   int getCurrentTurn() const { return currentTurn; }

   // data manipulators
   void increaseTurn() { currentTurn++; }
   void draw(ogstream & gout) const;
   void swap(const Move & move);
   void addPiece(Piece piece);

   void fillBoard();

   // Friend classes
   friend class TestPawn;
   friend class TestKing;

   // calls all getPossible move class for a funtion.
   std::set<Move> getMoves(int row, int col, Board& board) const;

   // overriding operators
   const Piece& operator[] (const Position& pos) const { return *board[pos.getRow()][pos.getCol()]; }
   const Piece& operator = (Piece* pRhs) {}
   Piece& operator[] (Position& pos) { return *board[pos.getRow()][pos.getCol()]; }

private:
   // private member variables
   Piece* board[8][8];
   int currentTurn;

   // private methods
   void setCurrentTurn(const int& turn) { currentTurn = turn; }
   std::set<Move> possibleMoves;
};