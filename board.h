/******************************************************************************
* BOARD
* The Board class handles all Board operations including drawing and moving
* pieces.
******************************************************************************/

#include <vector>
#include "uiDraw.h"

#pragma once

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
private:
   std::vector<std::vector<Piece>> board;
   int currentTurn = 0;

   void setCurrentTurn(const int& turn) { currentTurn = turn; }
   void fillBoard();
};