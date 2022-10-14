/**********************************************************************
 * GL Demo
 * Just a simple program to demonstrate how to create an Open GL window, 
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "test.h"
#include "king.h"

using namespace std;

/***************************************************
 * DRAW
 * Draw the current state of the game
 ***************************************************/
void draw(const  Board* board, const Interface & ui, const set <Move> & possible)
{
   ogstream gout;
   
   // draw the checkerboard
   gout.drawBoard();

   // draw any selections
   gout.drawHover(ui.getHoverPosition());
   gout.drawSelected(ui.getSelectPosition());

   // draw the possible moves
   for (auto it = possible.begin(); it != possible.end(); it++)
   {
      gout.drawPossible(it->getDest().getLocation());
   }
   //for (it = possible.begin(); it != possible.end(); ++it)
   //   gout.drawPossible(*it.g);

   board->draw(gout);
}

/*********************************************
 * MOVE 
 * Execute one movement. Return TRUE if successful
 *********************************************/
bool move(Board* board, int posFrom, int posTo)
{
   // do not move if a move was not indicated
   if (posFrom == -1 || posTo == -1)
      return false;
   assert(posFrom >= 0 && posFrom < 64);
   assert(posTo >= 0 && posTo < 64);

   std::set<Move> possiblePrevious;
   bool turn = false;

   // Condition statement to see which color's turn it is to move; if % 2 == 0 it is white's turn,
   // if 1 then it is black's turn.
   if (board->getCurrentTurn() % 2 == 0 && board->getPiece(posFrom / 8, posFrom % 8).isWhite())
   {
      // find the set of possible moves from our current location
      possiblePrevious = board->setMoves(posFrom / 8, posFrom % 8, *board);
      turn = true;
   }   
   else if (board->getCurrentTurn() % 2 == 1 && board->getPiece(posFrom / 8, posFrom % 8).isWhite() != true)
   {
      // find the set of possible moves from our current location
      possiblePrevious = board->setMoves(posFrom / 8, posFrom % 8, *board);
      turn = true;
   }

   auto it = possiblePrevious.find(Move(posFrom, posTo));
   // If the move is in the potential moves and turn is true than that piece is able to move.
   if ( it != possiblePrevious.end() && turn)
   {     
      board->swap(*it);
      return true;      
   }

   return false;

}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI,  void * board)
{
   std::set<Move> possibleMoves;
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Board* pBoard = (Board*) board;

   if (move(pBoard, pUI->getPreviousPosition(), pUI->getSelectPosition()))
      pUI->clearSelectPosition();

   else if (pUI->getSelectPosition() != -1)
   {
      if(pBoard->getCurrentTurn() % 2 == 0 && pBoard->getPiece(pUI->getSelectPosition() / 8, pUI->getSelectPosition() % 8).isWhite())
         possibleMoves = pBoard->setMoves(pUI->getSelectPosition() / 8, pUI->getSelectPosition() % 8, *pBoard);

      if (pBoard->getCurrentTurn() % 2 == 1 && !pBoard->getPiece(pUI->getSelectPosition() / 8, pUI->getSelectPosition() % 8).isWhite())
         possibleMoves = pBoard->setMoves(pUI->getSelectPosition() / 8, pUI->getSelectPosition() % 8, *pBoard);
   }
   
   // This being commented out seems to make no difference.
   //else
     // pUI->clearPreviousPosition();
   // draw the board
   draw(pBoard, *pUI, possibleMoves);
}

/********************************************************
 * PARSE
 * Determine the nature of the move based on the input.
 * This is the only function understanding Smith notation
 *******************************************************/
void parse(const string& textMove, int& positionFrom, int& positionTo)
{
   string::const_iterator it = textMove.cbegin();

   // get the source
   int col = *it - 'a';
   it++;
   int row = *it - '1';
   it++;
   positionFrom = row * 8 + col;

   // get the destination
   col = *it - 'a';
   it++;
   row = *it - '1';
   it++;
   positionTo = row * 8 + col;

   // capture and promotion information
   char capture = ' ';
   char piecePromotion = ' ';
   bool castleK = false;
   bool castleQ = false;
   bool enpassant = false;
   for (; it != textMove.end(); ++it)
   {
      switch (*it)
      {
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
      case 'k':   // !! you can't capture a king you silly!
         capture = tolower(*it);
         break;

      case 'c':  // short castling or king's castle
         castleK = true;
         break;
      case 'C':  // long castling or queen's castle
         castleQ = true;
         break;
      case 'E':  // En-passant
         enpassant = true;
         break;

      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         piecePromotion = *it;
         break;

      }
   }

   // error checking
   if (positionFrom < 0 || positionFrom >= 64 ||
       positionTo   < 0 || positionTo   >= 64)
      positionFrom = positionTo = -1;
}

/********************************************************
 * READ FILE
 * Read a file where moves are encoded in Smith notation
 *******************************************************/
void readFile(const char* fileName, Board* board)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return;

   // read the file, one move at a time
   string textMove;
   bool valid = true;
   while (valid && fin >> textMove)
   {
      int positionFrom;
      int positionTo;
      parse(textMove, positionFrom, positionTo);
      valid = move(board, positionFrom, positionTo);
   }

   // close and done
   fin.close();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   Test test;
   test.run();

   Interface ui("Chess");

   Board board(true);

   ui.run(callBack, &board);             

   return 0;
}
