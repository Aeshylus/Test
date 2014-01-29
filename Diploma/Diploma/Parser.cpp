#include "stdafx.h"

#include "Parser.h"

#include <boost\assign.hpp>
#include <locale>
#include "..\..\..\..\boost_1_53_0\boost\lexical_cast.hpp"

namespace
  {
  const int g_num_of_chanels = 5;
  const int g_number_of_values = 63;

  std::map<ParserError::ErrorType, std::string> g_error_massages = boost::assign::map_list_of
                                                                   (ParserError::E_NOT_ENOUGH_CHANGELS, "Not enough chanels in file")
                                                                   (ParserError::E_BAD_FILE, "Can't find file");
  }
//////////////////////////////////////////////////////////////////////////
Parser::Parser( const std::wstring& i_file_name )
  {
  m_file.open(i_file_name);
  if (!m_file.is_open())
    throw ParserError(ParserError::E_BAD_FILE);
  _Parse();
  }

//////////////////////////////////////////////////////////////////////////
Parser::~Parser()
  {
  m_file.close();
  }

//////////////////////////////////////////////////////////////////////////
int Parser::GetNumberOfChanels() const
  {
  return g_num_of_chanels;
  }

//////////////////////////////////////////////////////////////////////////
void Parser::_Parse()
  {
  m_file.imbue(std::locale("rus_rus.1251"));
  while(!m_file.eof())
      {
      std::wstring value;
      m_file >> value;
      if (value.find(_T("канал")) != std::wstring::npos)
        {
        // fill chanels with values from file
        _TChanel chanel;
        for (int i = 0; i < g_number_of_values; ++i)
          {
          std::wstring value;
          m_file >> value;
          chanel.push_back(boost::lexical_cast<float>(value));
          }

        m_chanels.push_back(chanel);
        }
      }
    

  if (m_chanels.size() != g_num_of_chanels)
    throw ParserError(ParserError::E_NOT_ENOUGH_CHANGELS);
  }

//////////////////////////////////////////////////////////////////////////
Parser::_TChanel Parser::GetChanel(int i_index) const
  {
  return m_chanels[i_index];
  }


//////////////////////////////////////////////////////////////////////////
ParserError::ParserError( ErrorType i_type )
  : m_type(i_type)
  {

  }

//////////////////////////////////////////////////////////////////////////
const char* ParserError::what() const 
  {
  return g_error_massages.at(m_type).c_str();
  }
