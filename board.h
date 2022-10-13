/******************************************************************************
* BOARD
* The Board class handles all Board operations including drawing and moving
* pieces.
******************************************************************************/
#pragma once
#include <vector>
#include <iostream>
#include "uiDraw.h"
#include "piece.h"



class Piece;

class Board
{
public:
   Board();
   void addPiece(Piece piece);
   Piece getPiece(const int& row, const int& col) const;
   int getCurrentTurn() const { return currentTurn; }
   void increaseTurn() { currentTurn++; }
   void draw(ogstream & gout) const;

   friend class TestPawn;
   friend class TestKing;
   std::set<Move> getMoves(int row, int col, Board& board) const;
   const Piece& operator[] (const Position& pos) const 
   {
      return *board[pos.getRow()][pos.getCol()];
   }
   const Piece& operator = (Piece* pRhs) {}
   Piece& operator[] (Position& pos)
   {
      return *board[pos.getRow()][pos.getCol()];
   }

private:
   Piece* board[8][8];
   int currentTurn = 0;

   void setCurrentTurn(const int& turn) { currentTurn = turn; }
   void fillBoard();
};