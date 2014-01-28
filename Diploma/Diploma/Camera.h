#pragma once

#include <boost/numeric/ublas/matrix.hpp>

//////////////////////////////////////////////////////////////////////////
/// incapsulates behavior of camre
class Camera
  {
  public:
    Camera(irr::scene::ISceneManager* ip_smgr, const irr::core::vector3df& i_pos, const irr::core::vector3df& i_target);

    void SetRotation(float i_angle, irr::core::vector3df i_rotation_axis);

    irr::core::vector3df GetTarget() const;
    irr::core::vector3df GetPosition() const;
    irr::core::vector3df GetUpVecotr() const;

    void SetTarget(const irr::core::vector3df& i_target);
    void SetPosition(const irr::core::vector3df& i_position);

    irr::core::vector3df ScreenToCameraCoordinates(CPoint i_coord) const;

  private:
    irr::scene::ISceneManager* mp_smgr;
    irr::scene::ICameraSceneNode* mp_camera;

    boost::numeric::ublas::matrix<float> m_transform_matrix;
    irr::core::vector3df                 m_start_pos;
    irr::core::vector3df                 m_start_up_vector;
  };