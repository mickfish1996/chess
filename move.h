/******************************************************************************************
 *
 ******************************************************************************************/
#pragma once
#include <iostream>
#include "position.h"

 /***********************************
 * MOVE
 * A quick dummy Move class to use for
 * testing other classes.
 ***********************************/
class Move {
private:
   Position source;
   Position dest;
   char pieceType;

   bool isWhite;
   bool capture;
   bool enpassant;
   bool promotion;
   bool castleK;
   bool castleQ;

public:
   Move();
   Move(const Position& sourcePosition);
   Move(const std::string move);
   Move(const int location1, const int location2);
   Position getDest() const { return dest; }
   Position getSource() const { return source; }
   std::string getSmith() const;


   void setSource(const Position sourcePos) { source = sourcePos; }
   void setDest(const Position destPos) { dest = destPos; }
   void setWhiteColor(const bool whiteColor) { this->isWhite = whiteColor; }
   void setCapture(const bool capture) { this->capture = capture; }
   void setEnPassant(const bool enpassant) { this->enpassant = enpassant; }
   void setPromotion(const bool promotion) { this->promotion = promotion; }
   void setCastleK(const bool cCastle) { castleK = cCastle; }
   void setCastleQ(const bool cCastle) { castleQ = cCastle; }
   void setPieceType(const char piece) { this->pieceType = piece; }


   bool operator== (const std::string& rhs) { return dest.getSmith() == rhs; }

   friend bool operator== (const Move& move1, const Move& move2);
   bool operator< (const Move& rhs) const { return dest.getLocation() < rhs.getDest().getLocation(); }

   friend class TestKing;
   friend class TestPawn;
};