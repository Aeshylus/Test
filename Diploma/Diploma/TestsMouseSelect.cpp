#include "stdafx.h"

#include "Camera.h"
#include "CDiploma3DView.h"
#include "SelectMouse.h"
#include "MButtonDownMovementLogic.h"
#include "RButtonDownMovementLogic.h"

#include <UnitTest++.h>

using namespace irr;

//////////////////////////////////////////////////////////////////////////
namespace
  {
  //////////////////////////////////////////////////////////////////////////
  class _MouseFixture
    {
    public:
      _MouseFixture()
        {
        m_view.Intialize(core::vector3df(0., 0., 0.), core::vector3df(0., 0., 0.));
        }


    protected:
      void TEST_NO_ACTION(CPoint i_start, CPoint i_finish)
        {
        m_mouse.OnMouseMove(&m_view, 0, i_start);
        m_mouse.OnMouseMove(&m_view, 0, i_finish);

        CHECK(m_view.GetCamera()->GetPosition().equals(core::vector3df(0., 0., 0.)));
        }

      void TEST_PAN(const CPoint& start, const CPoint& end)
        {
        MButtonDownMovementLogic().MakeMove(&m_view, start, end);

        auto camera = m_view.GetCamera();
        auto expected = m_view.GetCamera()->ScreenToCameraCoordinates(end) - m_view.GetCamera()->ScreenToCameraCoordinates(start);
        CHECK( camera->GetTarget().equals(expected));
        CHECK( camera->GetPosition().equals(expected));
        }

      void TEST_ROTATE(const CPoint& start, const CPoint& end, const core::vector3df& i_expected)
        {
        m_view.GetCamera()->SetPosition(core::vector3df(1., 0., 0.));
        RButtonDownMovementLogic().MakeMove(&m_view, start, end);
        CHECK( m_view.GetCamera()->GetPosition().equals(i_expected));
        }

      SelectMouse m_mouse;
      CDiploma3DView m_view;
    };
  }

//////////////////////////////////////////////////////////////////////////
SUITE(PanLogicMovement)
  {
  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, PanLogic)
    {
    TEST_PAN(CPoint(0,0), CPoint(10, 10));
    }
  }

//////////////////////////////////////////////////////////////////////////
SUITE(RotateLogicMovement)
  {
  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, Should_0_1_0_When_Rotate_90_Around_Z)
    {
    TEST_ROTATE(CPoint(0,0), CPoint(90, 0), core::vector3df(0., -1., 0));
    }
  }

//////////////////////////////////////////////////////////////////////////
SUITE(SelectMouseTests)
  {
  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, TestCameraRotationOnMouseMove)
    {
    CPoint start_point(0,0);
    CPoint end_point(90,0);

    m_view.GetCamera()->SetPosition(core::vector3df(1., 0., 0.));
    m_mouse.OnRButtonDown(&m_view, 0, start_point);
    m_mouse.OnMouseMove(&m_view, 0, end_point);
    m_mouse.OnRButtonUp(&m_view, 0, end_point);

    CHECK(m_view.GetCamera()->GetPosition().equals(core::vector3df(0., -1., 0.)));
    }

  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, TestCameraNoRotationAndPan)
    {
    TEST_NO_ACTION(CPoint(0,0), CPoint(10,0));
    }

  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, TestPanCameraOnMiddleButtonPressed)
    {
    CPoint start(0, 0);
    CPoint end(10,10);

    m_mouse.OnMButtonDown(&m_view, 0, start);
    m_mouse.OnMouseMove(&m_view, 0, end);
    m_mouse.OnMButtonUp(&m_view, 0, end);

    std::shared_ptr<Camera> camera = m_view.GetCamera();
    irr::core::vector3df expected = camera->ScreenToCameraCoordinates(end) - camera->ScreenToCameraCoordinates(start);

    CHECK(camera->GetPosition().equals(expected));
    CHECK(camera->GetTarget().equals(expected));
    }

  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_MouseFixture, Should_10_10_0_When_move_twice)
    {
    CPoint start1(0, 0);
    CPoint end1(5, 5);
    CPoint start2(10, 10);
    CPoint end2(15, 15);

    m_mouse.OnMButtonDown(&m_view, 0, start1);
    m_mouse.OnMouseMove(&m_view, 0, end1);
    m_mouse.OnMButtonUp(&m_view, 0, end1);
    
    m_mouse.OnMButtonDown(&m_view, 0, start2);
    m_mouse.OnMouseMove(&m_view, 0, end2);
    m_mouse.OnMButtonUp(&m_view, 0, end2);

    std::shared_ptr<Camera> camera = m_view.GetCamera();
    irr::core::vector3df expected = camera->ScreenToCameraCoordinates(end1) - camera->ScreenToCameraCoordinates(start1) + 
                                   (camera->ScreenToCameraCoordinates(end2) - camera->ScreenToCameraCoordinates(start2));

    CHECK(camera->GetPosition().equals(expected));
    CHECK(camera->GetTarget().equals(expected));
    }

  }