/************************************************************************
 * TEST
 ************************************************************************/
#pragma once
#include "testKing.h"
#include "testPawn.h"

/************************************************************************
 * TEST CLASS
 * Contains all Unit Tests
 ************************************************************************/
class Test
{
private:
   TestKing testKing;
   TestPawn testPawn;
public:
   void run();
};

void Test::run()
{
   testKing.run();
   testPawn.run();
}