/******************************************************************************************
 *
 ******************************************************************************************/

#include "position.h"
#include <sstream>

Position::Position(int r, int c)
{
   row = r;
   col = c;
}

bool Position::isValid()
{
   return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}

/***********************************************
 * Position
 * This constructor will set the position
 * based on the string that is recieved.
 ***********************************************/
Position::Position(const char* move)
{
   if (move[0] == 'a')
      col = 0;
   else if (move[0] == 'b')
      col = 1;
   else if (move[0] == 'c')
      col = 2;
   else if (move[0] == 'd')
      col = 3;
   else if (move[0] == 'e')
      col = 4;
   else if (move[0] == 'f')
      col = 5;
   else if (move[0] == 'g')
      col = 6;
   else if (move[0] == 'h')
      col = 7;
   else
      throw("ERROR out of range!");

   // subtract 49 because value is given in ascii value
   row = (int)move[1] - 49;
}

/***********************************************
 * getSmith
 * Will return the position in smith notation
 ***********************************************/
std::string Position::getSmith() const
{
   std::string sCol;
   switch (this->col)
   {
   case 0:
      sCol = "a";
      break;
   case 1:
      sCol = "b";
      break;
   case 2:
      sCol = "c";
      break;
   case 3:
      sCol = "d";
      break;
   case 4:
      sCol = "e";
      break;
   case 5:
      sCol = "f";
      break;
   case 6:
      sCol = "g";
      break;
   case 7:
      sCol = "h";
      break;
   }

   return sCol.append(std::to_string(row + 1));
}

/***********************************************
 * getLocation
 * Will return the position in smith notation
 ***********************************************/
int Position::getLocation() const
{
   return row * 8 + col;
}

/***********************************************
 * set
 * Will set the row and col
 ***********************************************/
void Position::set(const int r, const int c)
{
   row = r;
   col = c;
}

