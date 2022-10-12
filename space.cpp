#include "space.h"

Space::Space(const int& row, const int& col)
{
   position.setRow(row);
   position.setCol(col);
   pieceType = 's';
}

Space::Space()
{
   position.setRow(0);
   position.setCol(0);
   pieceType = 's';
}