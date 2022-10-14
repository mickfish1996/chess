/******************************************************************************
* TEST PAWN
* The TestPawn class contains all of the unit tests for the Pawn class.
******************************************************************************/

#pragma once
#include <iostream>
#include "pawn.h"
#include <assert.h>

class TestPawn
{
public:
   void debugMoves(const std::set<Move>& moves, const std::set<Move>& verifyMoves)
   {
      std::cout << "\nmoves: ";
      for (auto iter = moves.begin(); iter != moves.end(); iter++)
      {
         std::cout << iter->getSmith() << " ";
      }
      std::cout << std::endl;

      std::cout << "verifyMoves: ";
      for (auto iter = verifyMoves.begin(); iter != verifyMoves.end(); iter++)
      {
         std::cout << iter->getSmith() << " ";
      }
      std::cout << std::endl;
   }

   void run()
   {
      getMoves_blocked();
      getMoves_simple();
      getMoves_initial();
      getMoves_capture();
      getMoves_enPassant();
      getMoves_promotion();
      getRow_zeroes();
      getCol_zeroes();
      getRow_simple();
      getCol_simple();
   }

   /**********************************
   * ASCII Key
   * CAPITAL: Indicates a black piece.
   * lowercase: Indicates a white piece.
   * ".": Indicates a possible move.
   **********************************/

   /***************************************************************************
   * CREATE WHITE PAWN
   * Creates a standard white pawn so that we only have to change its
   * position in the unit tests.
   ***************************************************************************/
   Pawn createWPawn()
   {
      Position dummyPos = Position();
      Move dummyMove = Move(dummyPos);
      dummyMove.dest = dummyPos;

      Pawn pawn = Pawn();
      pawn.whiteColor = true;
      pawn.lastMove = dummyMove;
      pawn.nMoves = 0;

      return pawn;
   }

   /***************************************************************************
   * CREATE BLACK PAWN
   * Creates a standard black pawn so that we only have to change its
   * position in the unit tests.
   ***************************************************************************/
   Pawn createBPawn()
   {
      Position dummyPos = Position();
      Move dummyMove = Move(dummyPos);
      dummyMove.dest = dummyPos;

      Pawn pawn = Pawn();
      pawn.whiteColor = false;
      pawn.lastMove = dummyMove;
      pawn.nMoves = 0;

      return pawn;
   }

   /***************************************************************************
   * CREATE MOVE
   * Creates a move given a source and destination row and column. Used to
   * assist in test creation.
   ***************************************************************************/
   Move createMove(const int& sRow, const int& sCol, const int& dRow,
      const int& dCol, const char& piece)
   {
      Position source;
      source.row = sRow;
      source.col = sCol;

      Position dest;
      dest.row = dRow;
      dest.col = dCol;

      Move move;
      move.source = source;
      move.dest = dest;

      move.White = true;
      move.capture = false;
      move.enpassant = false;
      move.promotion = false;
      move.castle = false;
      move.pieceType = piece;

      return move;
   }

   /***********************************
   * GET POSSIBLE MOVES: Blocked Test
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8                     7
   * 7                     6
   * 6                     5
   * 5         P           4
   * 4         p           3
   * 3                     2
   * 2                     1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_blocked()
   {
      // Setup
      Board board;

      Pawn wPawn = createWPawn();
      wPawn.position.row = 3;
      wPawn.position.col = 3;
      wPawn.nMoves = 1;
      board.addPiece(wPawn);

      Pawn bPawn = createBPawn();
      bPawn.position.row = 4;
      bPawn.position.col = 3;
      board.addPiece(bPawn);

      std::set<Move> moves = { };
      std::set<Move> verifyMoves = { };

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);

   }  // Teardown

   /***********************************
   * GET POSSIBLE MOVES: Simple Test
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8                     7
   * 7                     6
   * 6                     5
   * 5     .               4
   * 4     p               3
   * 3                     2
   * 2                     1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_simple()
   {
      // Setup
      Pawn wPawn = createWPawn();
      wPawn.position.row = 3;
      wPawn.position.col = 1;
      wPawn.nMoves = 1;

      Board board = Board();

      std::set<Move> moves;
      Move move1 = createMove(3, 1, 4, 1, 'p');
      std::set<Move> verifyMoves = { move1 };

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);

   }  // Teardown

   /***********************************
   * GET POSSIBLE MOVES: Initial
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8                     7
   * 7                     6
   * 6                     5
   * 5                     4
   * 4     .               3
   * 3     .               2
   * 2     p               1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_initial()
   {
      // Setup
      Board board;
      Pawn wPawn = createWPawn();
      wPawn.position.row = 1;
      wPawn.position.col = 1;
      wPawn.nMoves = 0;
      board.addPiece(wPawn);

      std::set<Move> moves;

      Move move1 = createMove(1, 1, 2, 1, 'p');
      Move move2 = createMove(1, 1, 3, 1, 'p');

      std::set<Move> verifyMoves = { move1, move2 };

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);
      // TODO: Add more verification cases.

   }  // Teardown

   /***********************************
   * GET POSSIBLE MOVES: Capture
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8                     7
   * 7   P P P             6
   * 6     p               5
   * 5                     4
   * 4                     3
   * 3                     2
   * 2                     1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_capture()
   {
      // Setup
      Board board;

      Pawn wPawn = createWPawn();
      wPawn.position.row = 5;
      wPawn.position.col = 1;
      wPawn.nMoves = 3;
      board.addPiece(wPawn);

      Pawn bPawn1 = createBPawn();
      bPawn1.position.row = 6;
      bPawn1.position.col = 0;
      board.addPiece(bPawn1);
      Pawn bPawn2 = createBPawn();
      bPawn2.position.row = 6;
      bPawn2.position.col = 1;
      board.addPiece(bPawn2);
      Pawn bPawn3 = createBPawn();
      bPawn3.position.row = 6;
      bPawn3.position.col = 2;
      board.addPiece(bPawn3);

      std::set<Move> moves;

      Move move1 = createMove(5, 1, 6, 0, 'p');
      move1.capture = true;
      Move move2 = createMove(5, 1, 6, 2, 'p');
      move2.capture = true;

      std::set<Move> verifyMoves = { move1, move2 };

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);

   }  // Teardown

   /***********************************
   * GET POSSIBLE MOVES: En Passant
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8                     7
   * 7                     6
   * 6   . P .             5
   * 5   P p P             4
   * 4                     3
   * 3                     2
   * 2                     1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_enPassant()
   {
      // Setup
      Board board;
      board.currentTurn = 1;

      Pawn wPawn = createWPawn();
      wPawn.position.row = 4;
      wPawn.position.col = 1;
      wPawn.nMoves = 2;
      board.addPiece(wPawn);

      Pawn bPawn1 = createBPawn();
      bPawn1.position.row = 4;
      bPawn1.position.col = 0;
      bPawn1.enPassantTurn = 1;
      bPawn1.nMoves = 1;
      board.addPiece(bPawn1);

      Pawn bPawn2 = createBPawn();
      bPawn2.position.row = 5;
      bPawn2.position.col = 1;
      board.addPiece(bPawn2);

      Pawn bPawn3 = createBPawn();
      bPawn3.position.row = 4;
      bPawn3.position.col = 2;
      bPawn3.nMoves = 1;
      bPawn3.enPassantTurn = 1;
      board.addPiece(bPawn3);

      std::set<Move> moves;
      Move move1 = createMove(4, 1, 5, 0, 'p');
      Move move2 = createMove(4, 1, 5, 2, 'p');
      move1.enpassant = true;
      move2.enpassant = true;
      std::set<Move> verifyMoves = { move1, move2 };

      // Incrementing turn to simulate the next player's move.
      board.currentTurn++;

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);

   }  // Teardown

   /***********************************
   * GET POSSIBLE MOVES: Promotion
   * +---0-1-2-3-4-5-6-7---+
   * |                     |
   * 8     .               7
   * 7     p               6
   * 6                     5
   * 5                     4
   * 4                     3
   * 3                     2
   * 2                     1
   * 1                     0
   * |                     |
   * +---a-b-c-d-e-f-g-h---+
   ***********************************/
   void getMoves_promotion()
   {
      // Setup
      Board board;

      Pawn wPawn = createWPawn();
      wPawn.position.row = 6;
      wPawn.position.col = 1;
      wPawn.nMoves = 4;
      board.addPiece(wPawn);

      std::set<Move> moves;
      Move move1 = createMove(6, 1, 7, 1, 'p');
      move1.promotion = true;
      std::set<Move> verifyMoves = { move1 };

      // Exercise
      moves = wPawn.getPossibleMoves(board);

      // Verify
      assert(moves == verifyMoves);

   }  // Teardown

   void getRow_zeroes()
   {
      // Setup
      Pawn pawn = createWPawn();
      pawn.position.row = 0;
      pawn.position.col = 0;

      // Exercise
      int testRow = pawn.getRow();

      // Verify
      assert(testRow == 0);

   }  // Teardown

   void getCol_zeroes()
   {
      // Setup
      Pawn pawn = createWPawn();
      pawn.position.row = 0;
      pawn.position.col = 0;

      // Exercise
      int testRow = pawn.getCol();

      // Verify
      assert(testRow == 0);

   }  // Teardown

   void getRow_simple()
   {
      // Setup
      Pawn pawn = createWPawn();
      pawn.position.row = 5;
      pawn.position.col = 5;

      // Exercise
      int testRow = pawn.getRow();

      // Verify
      assert(testRow == 5);

   }  // Teardown

   void getCol_simple()
   {
      // Setup
      Pawn pawn = createWPawn();
      pawn.position.row = 5;
      pawn.position.col = 5;

      // Exercise
      int testRow = pawn.getCol();

      // Verify
      assert(testRow == 5);

   }  // Teardown
};