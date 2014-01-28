#include "stdafx.h"

#include "CDiploma3DView.h"
#include "Camera.h"
#include "IrrlichtFixture.h"
#include "SelectMouse.h"

#include <UnitTest++.h>

using namespace irr;

//////////////////////////////////////////////////////////////////////////
SUITE(CameraInteraction)
  {
  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_IrrlichtFixture, TestCameraRotationAroundAxisZ)
    {
    Camera camera(mp_device->getSceneManager(), core::vector3df(1., 0., 0.), core::vector3df(0., 0., 0.));
    camera.SetRotation(90., core::vector3df(0., 0., 1.));

    CHECK(camera.GetPosition().equals(core::vector3df(0., -1., 0.)));
    CHECK(camera.GetUpVecotr().equals(core::vector3df(0., 0., 1.)));
    }

  //////////////////////////////////////////////////////////////////////////
  TEST_FIXTURE(_IrrlichtFixture, TestCameraRotationAroundAxisY)
    {
    Camera camera(mp_device->getSceneManager(), core::vector3df(1., 0., 0.), core::vector3df(0., 0., 0.));
    camera.SetRotation(90., core::vector3df(0., 1., 0.));

    CHECK(camera.GetPosition().equals(core::vector3df(0., 0., 1.)));
    CHECK(camera.GetUpVecotr().equals(core::vector3df(-1., 0., 0.)));
    }

  }