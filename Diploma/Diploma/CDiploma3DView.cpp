#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "Diploma.h"
#endif

#include "CDiploma3DView.h"
#include "Camera.h"
#include "DiplomaDoc.h"
#include "IMouse.h"

#include <boost/bind.hpp>
#include <irrlicht.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace irr;

namespace
  {
  class CustomNode : public scene::ISceneNode
    {
    public:
      CustomNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
        : scene::ISceneNode(parent, mgr, id)
        {
        setAutomaticCulling(scene::EAC_OFF);
        Material.Wireframe = false;
        Material.Lighting = false;
        }

      virtual void OnRegisterSceneNode()
        {
        if (IsVisible)
          SceneManager->registerNodeForRendering(this);
        ISceneNode::OnRegisterSceneNode();
        }

      virtual void render()
        {
        video::IVideoDriver* driver = SceneManager->getVideoDriver();
        driver->setMaterial(Material);
        driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->draw3DLine(core::vector3df(0., 0., 0.), core::vector3df(1., 0., 0.), video::SColor(255, 0, 0, 255));
        driver->draw3DLine(core::vector3df(0., 0., 0.), core::vector3df(0., 1., 0.), video::SColor(0, 255, 0, 255));
        driver->draw3DLine(core::vector3df(0., 0., 0.), core::vector3df(0., 0., 1.), video::SColor(0, 0, 255, 255));
        
        driver->draw3DLine(core::vector3df(0., 0., 0.), m_rot_axis, video::SColor(255, 255, 255, 255));

        }
      virtual u32 getMaterialCount() const
        {
        return 1;
        }

      virtual video::SMaterial& getMaterial(u32 i)
        {
        return Material;
        }
      virtual const core::aabbox3df& getBoundingBox() const
        {
        return Box;
        }

      void SetRotAxis(const core::vector3df& i_rot_axis)
        {
        m_rot_axis = i_rot_axis;
        }

    private:
      core::aabbox3df   Box;
      video::S3DVertex Vertices[4];
      video::SMaterial Material;
      core::vector3df m_rot_axis;
    };
  }

IMPLEMENT_DYNCREATE(CDiploma3DView, CView)

BEGIN_MESSAGE_MAP(CDiploma3DView, CView)
  ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_RBUTTONDOWN()
  ON_WM_RBUTTONUP()
  ON_WM_MBUTTONDOWN()
  ON_WM_MBUTTONUP()
  ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
CDiploma3DView::CDiploma3DView()
  : mp_device(nullptr)
  , mp_driver(nullptr)
  , mp_smgr(nullptr)
  , mp_camera(nullptr)
  {
  auto app = ((CDiplomaApp*)AfxGetApp());
  if (app)
    app->m_update_view.connect(boost::bind(&CDiploma3DView::_UpdateView, this));
  }

//////////////////////////////////////////////////////////////////////////
CDiploma3DView::~CDiploma3DView()
  {
  }

//////////////////////////////////////////////////////////////////////////
BOOL CDiploma3DView::PreCreateWindow(CREATESTRUCT& cs)
  {
  return CView::PreCreateWindow(cs);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnDraw(CDC* dc)
  {
  CDiplomaDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  }

// CDiplomaView diagnostics

//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CDiploma3DView::AssertValid() const
  {
  CView::AssertValid();
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::Dump(CDumpContext& dc) const
  {
  CView::Dump(dc);
  }

//////////////////////////////////////////////////////////////////////////
CDiplomaDoc* CDiploma3DView::GetDocument() const // non-debug version is inline
  {
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiplomaDoc)));
  return (CDiplomaDoc*)m_pDocument;
  }
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnInitialUpdate()
  {
  Intialize(core::vector3df(20., 0., 0.), core::vector3df(0., 0., 0.));
  _Super::OnInitialUpdate();
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnDestroy()
  {
  if (mp_device)
    {
    mp_device->closeDevice();
    mp_device->drop();
    mp_device = nullptr;
    }
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnMouseMove( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnMouseMove(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnLButtonDown( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnLButtonDown(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnRButtonDown( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnRButtonDown(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnLButtonUp( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnLButtonUp(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnRButtonUp(UINT nFlags, CPoint point)
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnRButtonUp(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnMButtonUp( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnMButtonUp(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::OnMButtonDown( UINT nFlags, CPoint point )
  {
  auto p_mouse = GetDocument()->GetCurrentMouse();
  if (!p_mouse)
    return;

  p_mouse->OnMButtonDown(this, nFlags, point);
  }

//////////////////////////////////////////////////////////////////////////
CDiploma3DView::TCamera CDiploma3DView::GetCamera() const
  {
  return mp_camera;
  }

//////////////////////////////////////////////////////////////////////////
BOOL CDiploma3DView::OnEraseBkgnd( CDC* pDC )
  {
  return FALSE;
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::_UpdateView()
  {
  if (mp_device && mp_device->run())
    {
    mp_driver->beginScene(true, true, 0);
    mp_smgr->drawAll();
    mp_driver->endScene();
    }
  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::Intialize( const irr::core::vector3df& i_camera_pos, const irr::core::vector3df& i_camera_target )
  {
  SIrrlichtCreationParameters param;
  param.WindowId = reinterpret_cast<void*>(this->GetSafeHwnd());
  param.DriverType = irr::video::EDT_DIRECT3D9;
  mp_device = irr::createDeviceEx(param);

  mp_driver = mp_device->getVideoDriver();
  mp_smgr   = mp_device->getSceneManager();

  //create a camera and set its target
  mp_camera.reset(new Camera(mp_smgr, i_camera_pos, i_camera_target));

  myNode = new CustomNode(mp_smgr->getRootSceneNode(), mp_smgr, 333);
  myNode->drop();

  scene::ISceneNode* cube = mp_smgr->addCubeSceneNode(10);

  //textures
  cube->setMaterialTexture(0, mp_driver->getTexture("media/water-texture-01-.jpg"));
  cube->setMaterialTexture(1, mp_driver->getTexture("media/water-texture-01-.jpg"));
  cube->setMaterialFlag( video::EMF_LIGHTING, false );
  cube->setMaterialType( video::EMT_REFLECTION_2_LAYER );

  }

//////////////////////////////////////////////////////////////////////////
void CDiploma3DView::SetRotAxis( const core::vector3df& i_rot_axis )
  {
  static_cast<CustomNode*>(myNode)->SetRotAxis(i_rot_axis);
  }

// CDiplomaView message handlers
