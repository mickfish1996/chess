/***********************************************************************
 * Source File:
 *     Test King
 * Author:
 *     Kyler Melor, Michael FIsher
 * Description:
 *     Implement the unit tests for ensuring king movement is happeing
 *     how it should be happening.
 ************************************************************************/
#include "testKing.h"
#include <string>
#include "rook.h"


void TestKing::run()
{
   getMoves_free();
   getMoves_blocked();
   getMoves_capture();
   getMoves_castleKingMoved();
   getMoves_noCastleNoRooks();
   getMoves_castleRookMoved();
   getMoves_castleSuccess();
   getRow_typical();
   getCol_typical();
   getPosition_typical();
   isWhite_true();
   isWhite_false();
   assignPosition_e6();
   assignPosition_fail();
}

/******************************************
 * Check Position Function
 * Checks the position of a King.
 ******************************************/
bool TestKing::checkPos(Position pos, const std::string checkPos)
{
   return pos.getSmith() == checkPos;
}

/******************************************
 * GET POSSIBLE MOVES: Free
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5           k         4
 * 4                     3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_free()
{
   // Setup
   Board board;
   King king;
   king.whiteColor = true;
   king.position = Position("e5");
   board.addPiece(king);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);


   // Verify
   std::string strMoves[8] = { "e5d6", "e5e6", "e5f6", "e5d5", "e5f5", "e5d4", "e5e4", "e5f4" };

   assert(moves.size() == 8);

   for (int movesIndex = 0; movesIndex < 8; movesIndex++)
   {
      Move move = Move(strMoves[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: Blocked
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6         p p p       5
 * 5         p k p       4
 * 4         p p p       3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_blocked()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.position = Position("e5");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = true;
   pawn0.position = Position("d6");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = true;
   pawn1.position = Position("e6");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = true;
   pawn2.position = Position("f6");
   board.addPiece(pawn2);

   Pawn pawn3;
   pawn3.whiteColor = true;
   pawn3.position = Position("d5");
   board.addPiece(pawn3);

   Pawn pawn4;
   pawn4.whiteColor = true;
   pawn4.position = Position("f5");
   board.addPiece(pawn4);

   Pawn pawn5;
   pawn5.whiteColor = true;
   pawn5.position = Position("d4");
   board.addPiece(pawn5);

   Pawn pawn6;
   pawn6.whiteColor = true;
   pawn6.position = Position("e4");
   board.addPiece(pawn6);

   Pawn pawn7;
   pawn7.whiteColor = true;
   pawn7.position = Position("f4");
   board.addPiece(pawn7);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);

   // Verify
   assert(moves.empty());

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: Capture
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6         P P P       5
 * 5         P k P       4
 * 4         P P P       3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_capture()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.position = Position("e5");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = false;
   pawn0.position = Position("d6");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = false;
   pawn1.position = Position("e6");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = false;
   pawn2.position = Position("f6");
   board.addPiece(pawn2);

   Pawn pawn3;
   pawn3.whiteColor = false;
   pawn3.position = Position("d5");
   board.addPiece(pawn3);

   Pawn pawn4;
   pawn4.whiteColor = false;
   pawn4.position = Position("d5");
   board.addPiece(pawn4);

   Pawn pawn5;
   pawn5.whiteColor = false;
   pawn5.position = Position("d4");
   board.addPiece(pawn5);

   Pawn pawn6;
   pawn6.whiteColor = false;
   pawn6.position = Position("e4");
   board.addPiece(pawn6);

   Pawn pawn7;
   pawn7.whiteColor = false;
   pawn7.position = Position("f4");
   board.addPiece(pawn7);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);


   // Verify
   std::string strMoves[8] = { "e5d6p", "e5e6p", "e5f6p", "e5d5p", "e5f5p", "e5d4p", "e5e4p", "e5f4p" };

   assert(moves.size() == 8);

   for (int movesIndex = 0; movesIndex < 8; movesIndex++)
   {
      Move move = Move(strMoves[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: Castle King Moved
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2         p p p       1
 * 1   r       k     r   0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_castleKingMoved()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.nMoves = 1;
   king.position = Position("e1");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = true;
   pawn0.position = Position("d2");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = true;
   pawn1.position = Position("e2");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = true;
   pawn2.position = Position("f2");
   board.addPiece(pawn2);

   Rook rook0;
   rook0.whiteColor = true;
   rook0.position = Position("a1");
   board.addPiece(rook0);

   Rook rook1;
   rook1.whiteColor = true;
   rook1.position = Position("h1");
   board.addPiece(rook1);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);

   // Verify
   std::string strMoves[2] = { "e1f1", "e1d1" };

   assert(moves.size() == 2);

   for (int movesIndex = 0; movesIndex < 2; movesIndex++)
   {
      Move move = Move(strMoves[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: Castle Rook Moved
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2         p p p       1
 * 1   r       k     r   0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_castleRookMoved()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.position = Position("e1");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = true;
   pawn0.position = Position("d2");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = true;
   pawn1.position = Position("e2");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = true;
   pawn2.position = Position("f2");
   board.addPiece(pawn2);

   Rook rook0;
   rook0.whiteColor = true;
   rook0.nMoves = 1;
   rook0.position = Position("a1");
   board.addPiece(rook0);

   Rook rook1;
   rook1.whiteColor = true;
   rook1.nMoves = 1;
   rook1.position = Position("h1");
   board.addPiece(rook1);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);

   // Verify
   std::string strMoves[2] = { "e1f1", "e1d1" };

   assert(moves.size() == 2);

   for (int movesIndex = 0; movesIndex < 2; movesIndex++)
   {
      Move move = Move(strMoves[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: No Castle No Rooks
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2         p p p       1
 * 1     p     k   p     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_noCastleNoRooks()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.position = Position("e1");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = true;
   pawn0.position = Position("d2");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = true;
   pawn1.position = Position("e2");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = true;
   pawn2.position = Position("f2");
   board.addPiece(pawn2);

   Pawn pawn3;
   pawn3.whiteColor = true;
   pawn3.position = Position("b1");
   board.addPiece(pawn3);

   Pawn pawn4;
   pawn4.whiteColor = true;
   pawn4.position = Position("g1");
   board.addPiece(pawn4);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);

   // Verify
   std::string strMoves[2] = { "e1f1", "e1d1" };

   assert(moves.size() == 2);

   for (int movesIndex = 0; movesIndex < 2; movesIndex++)
   {
      Move move = Move(strMoves[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET POSSIBLE MOVES: Castle Success
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2         p p p       1
 * 1   r       k     r   0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getMoves_castleSuccess()
{
   // Setup
   Board board;

   King king;
   king.whiteColor = true;
   king.position = Position("e1");
   board.addPiece(king);

   Pawn pawn0;
   pawn0.whiteColor = true;
   pawn0.position = Position("d2");
   board.addPiece(pawn0);

   Pawn pawn1;
   pawn1.whiteColor = true;
   pawn1.position = Position("e2");
   board.addPiece(pawn1);

   Pawn pawn2;
   pawn2.whiteColor = true;
   pawn2.position = Position("f2");
   board.addPiece(pawn2);

   Rook rook0;
   rook0.whiteColor = true;
   rook0.position = Position("a1");
   rook0.nMoves = 0;
   board.addPiece(rook0);

   Rook rook1;
   rook1.whiteColor = true;
   rook1.position = Position("h1");
   rook1.nMoves = 0;
   board.addPiece(rook1);

   // Exercise
   std::set<Move> moves = king.getPossibleMoves(board);

   // Verify
   std::string strMove[4] = { "e1f1", "e1d1", "e1g1c", "e1c1c" };

   assert(moves.size() == 4);

   for (int movesIndex = 0; movesIndex < 2; movesIndex++)
   {
      Move move = Move(strMove[movesIndex]);
      auto it = moves.find(move);
      assert(it != moves.end());
   }

   // Teardown
}

/******************************************
 * GET ROW: Typical
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7                     6
 * 6                     5
 * 5                     4
 * 4         k           3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getRow_typical()
{
   // Setup
   King king;
   king.whiteColor = true;
   king.position = Position("d4");

   // Exercise
   int row = king.getRow();

   // Verify
   assert(row == 3);

   // Teardown
}

/******************************************
 * GET COLUMN: Typical
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7     k               6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getCol_typical()
{
   // Setup
   King king;
   king.whiteColor = true;
   king.position = Position("b7");

   // Exercise
   int col = king.getCol();

   // Verify
   assert(col == 1);

   // Teardown
}

/******************************************
 * GET POSITION: Typical
 * +---0-1-2-3-4-5-6-7---+
 * |                     |
 * 8                     7
 * 7     k               6
 * 6                     5
 * 5                     4
 * 4                     3
 * 3                     2
 * 2                     1
 * 1                     0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ******************************************/
void TestKing::getPosition_typical()
{
   // Setup
   King king;
   king.whiteColor = true;
   king.position = Position("b7");

   // Exercise
   Position pos = king.getPosition();

   // Verify
   assert(checkPos(pos, "b7"));

   // Teardown
}

/******************************************
 * IS WHITE: True
 * Expecting result true in testing isWhite().
 ******************************************/
void TestKing::isWhite_true()
{
   // Setup
   King king;
   king.whiteColor = true;

   // Exercise
   bool color = king.isWhite();

   // Verify
   assert(color == true);

   // Teardown
}

/******************************************
 * IS WHITE: False
 * Expecting result false in testing isWhite().
 ******************************************/
void TestKing::isWhite_false()
{
   // Setup
   King king;
   king.whiteColor = false;

   // Exercise
   bool color = king.isWhite();

   // Verify
   assert(color == false);

   // Teardown
}

/******************************************
 * ASSIGN POSITION: E6
 * Position of King should be E6.
 ******************************************/
void TestKing::assignPosition_e6()
{
   // Setup
   King king;

   // Exercise
   king.assignPosition("e6");

   // Verify
   std::string pos = king.position.getSmith();

   assert(checkPos(king.position, "e6"));
}

/******************************************
* ASSIGN POSITION: Fail
* Function assignPosition() should fail and return the
* default value of position, or A1.
******************************************/
void TestKing::assignPosition_fail()
{
   // Setup
   King king;

   // Exercise
   king.assignPosition("j6");

   // Verify
   assert(checkPos(king.position, "a1"));
}
