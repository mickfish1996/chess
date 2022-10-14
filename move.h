/***********************************************************************
 * Header File:
 *     Move
 * Author:
 *     Kyler Melor, Michael Fisher
 * Description:
 *     The definition of all the needed atributes of Move
 ************************************************************************/
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

   bool White;
   bool capture;
   bool enpassant;
   bool promotion;
   bool castle;

public:
   // constructors
   Move();
   Move(const Position& sourcePosition);
   Move(const std::string move);
   Move(const int location1, const int location2);

   // getters
   Position getDest() const { return dest; }
   Position getSource() const { return source; }
   char getType() const { return pieceType; }
   bool getCastleK() const { return castleK; }
   bool getCastleQ() const { return castleQ; }
   std::string getSmith() const;
   bool isWhite() const { return White; }
   bool isEnpassant() const { return enpassant; }
   bool isPromotion() const { return promotion; }
   bool isCastle() const { return castle; }

   // setters
   void setSource(const Position sourcePos) { source = sourcePos; }
   void setDest(const Position destPos) { dest = destPos; }
   void setWhiteColor(const bool whiteColor) { this->White = whiteColor; }
   void setCapture(const bool capture) { this->capture = capture; }
   void setEnPassant(const bool enpassant) { this->enpassant = enpassant; }
   void setPromotion(const bool promotion) { this->promotion = promotion; }
   void setCastle(const bool cCastle) { castle = cCastle; }
   void setPieceType(const char piece) { this->pieceType = piece; }

   // operators
   bool operator== (const std::string& rhs) { return dest.getSmith() == rhs; }
   friend bool operator== (const Move& move1, const Move& move2);
   bool operator< (const Move& rhs) const { return dest.getLocation() < rhs.getDest().getLocation(); }

   // friend classes.
   friend class TestKing;
   friend class TestPawn;
};