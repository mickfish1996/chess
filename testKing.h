/******************************************************************************
* TEST KING
* The TestKing class contains all of the unit tests for the King class.
******************************************************************************/
#pragma once
#include <cassert>
#include <set>
#include "king.h"
#include "pawn.h"
#include "position.h"
#include "board.h"
#include <string>

class TestKing
{
public:
   void run();

private:
   bool checkPos(Position pos, const std::string checkPos);

   // Tests on getMoves.
   void getMoves_free();
   void getMoves_blocked();
   void getMoves_capture();
   void getMoves_castleKingMoved();
   void getMoves_castleRookMoved();
   void getMoves_noCastleNoRooks();
   void getMoves_castleSuccess();

   // Tests on getRow and getCol
   void getRow_typical();
   void getCol_typical();

   // Test on getPosition
   void getPosition_typical();

   // Tests on isWhite
   void isWhite_true();
   void isWhite_false();

   // Tests on assignPosition
   void assignPosition_e6();
   void assignPosition_fail();
};