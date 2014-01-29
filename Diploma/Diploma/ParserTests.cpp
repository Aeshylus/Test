#include "stdafx.h"

#include "Parser.h"

#include <UnitTest++.h>

SUITE(ParserTests)
  {
  TEST(ReadNumberOfChanels)
    {
    Parser parser(_T("TestData\\Test.txt"));
    CHECK_EQUAL(5, parser.GetNumberOfChanels());
    }
  }