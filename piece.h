/******************************************************************************
* PIECE
* The Piece class contains all information about the pieces, including
* inherited pieces. Each piece has its own class and contains information about
* the piece's last move, color, position, and number of times moved.
******************************************************************************/

#pragma once
#include <set>
#include "position.h"
#include "move.h"
#include <vector>
#include "board.h"
#include "uiDraw.h"

class Board;

/***********************************
* PIECE Class
***********************************/
class Piece {
protected:
   Position position;
   bool whiteColor;
   Move lastMove;
   int nMoves;
   char pieceType;
   int enPassantTurn;
public:
   Piece();
   int getRow() { return position.getRow(); }
   int getCol() { return position.getCol(); }
   Position getPosition() const { return position; }
   int getNMoves() const { return nMoves; }
   char getType() const { return pieceType; }
   int getEnPassantTurn() const { return enPassantTurn; }
   Position getPreviousPosition() const { return lastMove.getSource(); }
   virtual std::set<Move> getPossibleMoves(const Board& board);

   void setRow(int& r) { position.setRow(r); }
   void setCol(int& c) { position.setCol(c); }
   void setEnPassantTurn(const Board& board);
   virtual void draw(ogstream& gout) const {}
   void move() {}
   bool isWhite() const { return whiteColor; }
   void assignPosition(const char* position);
   void assignPosition(const int row, const int col) { position = Position(row, col); }
   void setTurn(int turn) { nMoves = turn; }
   bool operator== (Piece rhs) const { return pieceType == rhs.getType(); }
};

class Rook : public Piece
{
public:
   friend class TestKing;
   Rook() { pieceType = 'r'; }
   void draw(ogstream& gout) const;

};