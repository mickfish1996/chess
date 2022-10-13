#pragma once
#include "piece.h"

class Space :
   public Piece
{
private:
   //Position position;
public:
   Space(const int& row, const int& col);
   Space();
   void draw(ogstream gout) {}
   //void setRow(const int &r) { position.setRow(r); }
   //void setCol(const int &c) { position.setCol(c); }
};