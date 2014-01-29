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

    int GetNumberOfChanels() const;
    _TChanel GetChanel(int i_index) const;

  private:
    void _Parse();

  private:
    std::wfstream m_file;
    _TChanels m_chanels;
  };

//////////////////////////////////////////////////////////////////////////
///
class ParserError : public std::exception
  {
  public:
    enum ErrorType
      {
      E_NOT_ENOUGH_CHANGELS,
      E_BAD_FILE
      };

  public:
    ParserError(ErrorType i_type);
    virtual const char* what() const override;

  private:
    ErrorType m_type;
  };