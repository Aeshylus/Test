#pragma once

class _IrrlichtFixture
  {
  public:
    //////////////////////////////////////////////////////////////////////////
    _IrrlichtFixture()
      {
      mp_device = irr::createDevice();
      }

    //////////////////////////////////////////////////////////////////////////
    ~_IrrlichtFixture()
      {
      mp_device->closeDevice();
      mp_device->drop();
      mp_device = nullptr;
      }

  protected:
    //data
    irr::IrrlichtDevice* mp_device;
  };
