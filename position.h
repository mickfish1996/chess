/******************************************************************************************
 * POSITION
 * The Position class keeps track of where the pieces are.
 ******************************************************************************************/
#pragma once
#include <iostream>
#include <sstream>

class Position {
public:
   Position() : row(0), col(0) { }
   Position(int r, int c);
   Position(const char* move);
   friend class TestPawn;
   friend class TestKing;
   int getRow() const { return row; }
   int getCol() const { return col; }
   int getLocation() const;
   std::string getSmith() const;

   void setRow(const int r) { row = r; }
   void setCol(const int c) { col = c; }
   void setLoc(const int loc);
   void set(const int r, const int c);
   bool isValid();
   void adjustRow(const int adjustRow, int next) { row += (adjustRow * next); }
   void adjustCol(const int adjustCol) { col += adjustCol; }

   bool operator== (Position rhs) const { return getLocation() == rhs.getLocation(); }
   Position operator=  (std::string rhs) { Position(rhs.c_str()); }

private:
   int row = 0;
   int col = 0;
};