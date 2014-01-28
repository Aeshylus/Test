#pragma once

//////////////////////////////////////////////////////////////////////////
///
class IMouse
  {
  public:
    virtual void OnMouseMove(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0;
    
    virtual void OnLButtonUp(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0; 
    virtual void OnLButtonDown(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0; 
    virtual void OnRButtonUp(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0; 
    virtual void OnRButtonDown(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0; 

    virtual void OnMButtonDown(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0; 
    virtual void OnMButtonUp(CWnd* ip_wnd, UINT nFlags, CPoint point ) = 0;
    
    virtual ~IMouse()
      {

      }
  };