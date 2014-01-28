#include "stdafx.h"

#include "Camera.h"

#include <cmath>


using namespace irr;
using namespace boost::numeric::ublas;

namespace
  {
  const int g_transform_matrix_size = 4;
  const float M_PI = 3.1415926535;
  
  //////////////////////////////////////////////////////////////////////////
  void _MakeMatrixIndentity(matrix<float>& io_matrix)
    {
    for (size_t i = 0; i < io_matrix.size1(); ++i)
      for(size_t j = 0; j < io_matrix.size2(); ++j)
        io_matrix(i, j) = i == j ?  1. : 0.;
    }

  //////////////////////////////////////////////////////////////////////////
  matrix<float> _CreateRotationMatrix(float i_angle, const irr::core::vector3df& i_rot_axis)
    {
    matrix<float> result(4, 4);
    _MakeMatrixIndentity(result);

    result(0, 0) = std::cos(i_angle) + i_rot_axis.X*i_rot_axis.X * (1 - std::cos(i_angle));
    result(0, 1) = i_rot_axis.X*i_rot_axis.Y*(1 - std::cos(i_angle)) - i_rot_axis.Z*std::sin(i_angle);
    result(0, 2) = i_rot_axis.X*i_rot_axis.Z*(1 - std::cos(i_angle)) + i_rot_axis.Y * std::sin(i_angle);
    result(1, 0) = i_rot_axis.Y*i_rot_axis.X*(1 - std::cos(i_angle)) + i_rot_axis.Z * std::sin(i_angle);
    result(1, 1) = std::cos(i_angle) + i_rot_axis.Y * i_rot_axis.Y * (1 - std::cos(i_angle));
    result(1, 2) = i_rot_axis.Y*i_rot_axis.Z*(1 - std::cos(i_angle)) - i_rot_axis.X * std::sin(i_angle);
    result(2, 0) = i_rot_axis.Z*i_rot_axis.X*(1 - std::cos(i_angle)) - i_rot_axis.Y * std::sin(i_angle);
    result(2, 1) = i_rot_axis.Z*i_rot_axis.Y*(1 - std::cos(i_angle)) + i_rot_axis.X * std::sin(i_angle);
    result(2, 2) = std::cos(i_angle) + i_rot_axis.Z * i_rot_axis.Z * (1 - std::cos(i_angle));
    return result;
    }

  //////////////////////////////////////////////////////////////////////////
  core::vector3df _Transform(const core::vector3df& i_vector_to_transform, const matrix<float>& i_transform_matrix)
    {
    vector<float> new_vec(4); 
    new_vec(0) = i_vector_to_transform.X;
    new_vec(1) = i_vector_to_transform.Y;
    new_vec(2) = i_vector_to_transform.Z;
    new_vec(3) = 1;
    new_vec = prod(new_vec, i_transform_matrix);
    return core::vector3df(new_vec(0), new_vec(1), new_vec(2));
    }
  }

//////////////////////////////////////////////////////////////////////////
Camera::Camera( irr::scene::ISceneManager* ip_smgr, const irr::core::vector3df& i_pos, const irr::core::vector3df& i_target ) 
  : mp_smgr(ip_smgr)
  , mp_camera(ip_smgr->addCameraSceneNode(0, i_pos, i_target))
  , m_transform_matrix(g_transform_matrix_size, g_transform_matrix_size)
  , m_start_pos(i_pos)
  , m_start_up_vector(irr::core::vector3df(0., 0., 1.))
  {
  _MakeMatrixIndentity(m_transform_matrix);
  mp_camera->setUpVector(m_start_up_vector);
  }

//////////////////////////////////////////////////////////////////////////
void Camera::SetRotation( float i_angle, irr::core::vector3df i_rotation_axis )
  {
  float angle = i_angle * M_PI/180;

  //update transform matrix
  matrix<float> rot_matrix = _CreateRotationMatrix(angle, i_rotation_axis);
  m_transform_matrix = prod(m_transform_matrix, rot_matrix);
  
  //apply new pos
  auto new_pos = _Transform(m_start_pos - mp_camera->getTarget(), m_transform_matrix);
  mp_camera->setPosition(new_pos + mp_camera->getTarget());

  //apply new up vector
  auto new_up_vector = _Transform(m_start_up_vector, m_transform_matrix);
  mp_camera->setUpVector(new_up_vector);
  }

//////////////////////////////////////////////////////////////////////////
irr::core::vector3df Camera::GetTarget() const
  {
  return mp_camera->getTarget();
  }

//////////////////////////////////////////////////////////////////////////
void Camera::SetTarget( const irr::core::vector3df& i_target )
  {
  mp_camera->setTarget(i_target);
  }

//////////////////////////////////////////////////////////////////////////
void Camera::SetPosition( const irr::core::vector3df& i_position )
  {
  mp_camera->setPosition(i_position);
  m_start_pos = i_position;
  }

//////////////////////////////////////////////////////////////////////////
irr::core::vector3df Camera::GetPosition() const
  {
  return mp_camera->getPosition();
  }

//////////////////////////////////////////////////////////////////////////
irr::core::vector3df Camera::GetUpVecotr() const
  {
  return mp_camera->getUpVector();
  }

//////////////////////////////////////////////////////////////////////////
irr::core::vector3df Camera::ScreenToCameraCoordinates( CPoint i_coord ) const
  {
  return mp_smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(core::vector2di(i_coord.x, i_coord.y), mp_camera).end;
  }
