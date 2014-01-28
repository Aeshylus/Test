#include "stdafx.h"
#include "GridRenderer.h"

#include <boost/lexical_cast.hpp>

namespace
  {
  const int g_top_bottom_margin = 5;

  const int g_value_width  = 12;
  const int g_value_height = 10;

  //////////////////////////////////////////////////////////////////////////
  void _DrawValue(CDC* ip_dc, CPoint i_top_left, int i_value)
    {
    CFont* pOldFont = ip_dc->GetCurrentFont();

    CFont font;
    font.CreateFont(13, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, 
      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
      CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE, nullptr);
    ip_dc->SelectObject(&font);

    CRect text_region(i_top_left, CSize(g_value_width, g_value_height));

    std::wstring value_text = boost::lexical_cast<std::wstring>(i_value);
    ip_dc->DrawText(value_text.c_str(), &text_region, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    ip_dc->SelectObject(pOldFont);
    }
  }

//////////////////////////////////////////////////////////////////////////
void GridRenderer::RenderGrid( CDC* ip_dc, const RenderInfo& i_info)
  {
  // draw caption
  auto text_height = ip_dc->GetTextExtent(i_info.m_grid_caption.c_str()).cy; //get text height
  CRect text_region(CPoint(i_info.m_top_left.x, i_info.m_top_left.y - 20), CSize(i_info.m_width, text_height));
  ip_dc->DrawText(i_info.m_grid_caption.c_str(), &text_region, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

  CPen pen_main_frm;
  pen_main_frm.CreatePen(PS_SOLID, 3, RGB(0,0,0));
  ip_dc->SelectObject(&pen_main_frm);

  // draw main frame
  ip_dc->Rectangle(CRect(i_info.m_top_left, CSize(i_info.m_width, i_info.m_hieght)));

  // draw grid
  CPoint center_line_coord(i_info.m_top_left.x + i_info.m_width/2, i_info.m_top_left.y);
  
  LOGBRUSH logBrush;
  logBrush.lbStyle = BS_SOLID;
  logBrush.lbColor = RGB(20,20,20);
  
  //Text info
  

  CPen ditherPen; 
  ditherPen.CreatePen(PS_DOT|PS_GEOMETRIC, 1, &logBrush); // Here is an error 
  
  // Draw line 
  ip_dc->SelectObject(&ditherPen); 
  ip_dc->MoveTo(center_line_coord.x, center_line_coord.y); 
  ip_dc->LineTo(center_line_coord.x, center_line_coord.y + i_info.m_hieght); 

  CPoint left(i_info.m_top_left.x, i_info.m_top_left.y + g_top_bottom_margin);
  CPoint right(i_info.m_top_left.x + i_info.m_width, i_info.m_top_left.y + g_top_bottom_margin);

  int num_of_horiz_lines = int(i_info.m_num_max_of_points/3) + 1;
  int shift = (int) std::ceil(double((i_info.m_hieght - 2 * g_top_bottom_margin)/(num_of_horiz_lines - 1)));
  for (int i = 0; i < num_of_horiz_lines; ++i)
    {
    ip_dc->MoveTo(left); 
    ip_dc->LineTo(right);
    CPoint value_text_top_left(left.x - g_value_width - 4, left.y - g_value_height/2);
    _DrawValue(ip_dc, value_text_top_left, i * 3);
    left.y += shift;
    right.y += shift;
    }
  }

