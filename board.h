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
   
   // Getters
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
   Piece* board[8][8];
   int currentTurn;
   std::set<Move> possibleMoves;

   void setCurrentTurn(const int& turn) { currentTurn = turn; }
};