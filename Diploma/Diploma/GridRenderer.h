#pragma once

//////////////////////////////////////////////////////////////////////////
///
struct RenderInfo
  {
  static int const m_num_max_of_points = 63;
  CPoint m_top_left;
  int    m_width;
  int    m_hieght;
  std::wstring m_grid_caption;
  };

//////////////////////////////////////////////////////////////////////////
///
class GridRenderer
  {
  public:
    void RenderGrid(CDC* ip_dc, const RenderInfo& i_info);

  private:
    int m_width;
    int m_hight;
    CDC*  mp_dc;
  };