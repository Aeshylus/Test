#pragma once

//////////////////////////////////////////////////////////////////////////
///
class Parser
  {
  typedef std::vector<float> _TChanel;
  typedef std::vector<_TChanel> _TChanels;

  public:
    Parser(const std::wstring& i_file_name);
    ~Parser();
    int GetNumberOfChanels();
  
  private:
    void _Parse();

  private:
    std::wfstream m_file;
  };

//////////////////////////////////////////////////////////////////////////
///
class ParserError : public std::exception
  {
  public:

  };