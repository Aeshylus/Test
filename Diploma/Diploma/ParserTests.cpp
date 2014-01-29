#include "stdafx.h"

#include "Parser.h"

#include <UnitTest++.h>

SUITE(ParserTests)
  {
  //////////////////////////////////////////////////////////////////////////
  TEST(ReadNumberOfChanels)
    {
    Parser parser(_T("TestData\\Test.txt"));
    CHECK_EQUAL(5, parser.GetNumberOfChanels());
    }

  //////////////////////////////////////////////////////////////////////////
  TEST(CheckValues)
    {
    Parser parser(_T("TestData\\Test.txt"));
    std::vector<float> chanel_0 = parser.GetChanel(0);
    
    const int chanel_size = 63;
    float expected[chanel_size] = {-0.515, -1.987, -1.987, -1.987, -1.987, -1.987, 
                          -1.987, -1.987, -1.990, -1.987, -1.987, -1.990, 
                          -1.987, -1.990, -1.987, -1.987, -1.987, -1.987,
                          -1.987, -1.992, -1.990, -1.990, -1.987, -1.985, 
                          -1.987, -1.987, -1.987, -1.987, -1.987, -1.990,
                          -1.990, -1.987, -1.990, -1.987, -1.985, -1.990,
                          -1.990, -1.985, -1.987, -1.987, -1.987, -1.985,
                          -1.987, -1.987, -1.987, -1.985, -1.987, -1.987,
                          -1.990, -1.987, -1.987, -1.990, -1.987, -1.987,
                          -1.985, -1.990, -1.987, -1.987, -1.987, -1.987,
                          -1.990, -1.987, -1.987};
    
    CHECK_EQUAL(chanel_size, chanel_0.size());
    for (size_t i = 0; i < chanel_0.size(); ++i)
      CHECK_EQUAL(expected[i], chanel_0[i]);
    }
  }