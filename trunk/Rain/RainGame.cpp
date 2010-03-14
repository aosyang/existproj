#include "RainGame.h"
#include "Zone.h"

RainGame::RainGame()
: m_Scene(NULL),
  m_Camera(NULL),
  m_LookAtPos(0.0f, 1.0f, 0.0f),
  m_DebugRender(true),
  m_SelectedZone(NULL)
{
}

void RainGame::StartGame()
{
	// 创建场景
	m_Scene = new SceneGraph();

	m_Camera = FACTORY_CREATE(m_Scene, Camera);
	m_Camera->SetFarClippingDistance(1000.0f);

	DistantViewObject* sky = FACTORY_CREATE(m_Scene, DistantViewObject);
	BaseMesh* skyMesh = MeshManager::Instance().GetByName("sky\\skybox.emd");
	sky->SetMesh(skyMesh);

	//SceneSerializer serializer;
	//serializer.SetSceneGraph(m_Scene);
	//serializer.Unserialize("../data/city.emp");

	REGISTER_FACTORY(Zone);

	Zone* zone = FACTORY_CREATE(m_Scene, Zone);
	zone->SetPosition(Vector3f(-10.0f, 0.0f, 50.0f));

	//zone = FACTORY_CREATE(m_Scene, Zone);
	//zone->SetPosition(Vector3f(0.0f, 0.0f, 50.0f));
	//zone->SetRadius(20.0f);
	//zone->SetAltitude(2.0f);

	//zone = FACTORY_CREATE(m_Scene, Zone);
	//zone->SetPosition(Vector3f(-10.0f, 0.0f, 40.0f));
	//zone->SetRadius(35.0f);
}

void RainGame::Shutdown()
{
	// 删除场景
	SAFE_DELETE(m_Scene);
}

void RainGame::OnKeyPressed(unsigned int key)
{
	switch (key)
	{
		// P键控制开/关debug渲染
	case KC_P:
		m_DebugRender = !m_DebugRender;
		break;
	}
}

void RainGame::OnResizeWindow(unsigned int width, unsigned int height)
{
	// 窗口缩放以后要更新摄像机的纵横比...
	float aspect = (float)width / height;
	if (m_Camera)
	{
		m_Camera->SetAspect(aspect);
		
		// ...以及投影矩阵
		Renderer::Instance().SetProjectionMatrix(m_Camera->GetProjMatrix());
	}
}

void RainGame::Update(unsigned long deltaTime)
{
	float forward = 0.0f;
	float right = 0.0f;

	static float speed = 0.04f;

	if (Input::Instance().GetKeyDown(KC_W))
		forward += speed * deltaTime;
	if (Input::Instance().GetKeyDown(KC_S))
		forward += -speed * deltaTime;
	if (Input::Instance().GetKeyDown(KC_A))
		right += -speed * deltaTime;
	if (Input::Instance().GetKeyDown(KC_D))
		right += speed * deltaTime;

	Vector3f vecRight = m_Camera->WorldTransform().GetRightVector();
	m_LookAtPos += CrossProduct(Vector3f(0.0f, 1.0f, 0.0f), vecRight) * forward;
	m_LookAtPos += vecRight * right;

	static float heading = 0.0f;
	static float pitch = 75.0f / 180.0f * Math::kPi;

	static float range = 200.0f;

	// 使用鼠标右键调整摄像机视角
	if (Input::Instance().GetMouseButtonDown(MB_Right))
	{
		float x = -(float)Input::Instance().GetMouseRelX() / 5.0f;
		float y = -(float)Input::Instance().GetMouseRelY() / 5.0f;

		heading += x / 100.0f;
		pitch += y / 100.0f;

		heading = Math::Repeat(0.0f, Math::k2Pi, heading);
		pitch = Math::Clamp(0.0f, Math::kPiOver2, pitch);

	}
	UpdateCamera(heading, pitch, range);

	// 更新区域之间关系
	ZoneManager::Instance().Update(deltaTime);
	m_Scene->UpdateScene(deltaTime);
}

void RainGame::UpdateCamera(float heading, float pitch, float range)
{
	Quaternion quatHeading, quatPitch;
	quatHeading.CreateFromLocalAxisAngle(Vector3f(0.0f, 1.0f, 0.0f), heading);
	quatPitch.CreateFromLocalAxisAngle(Vector3f(1.0f, 0.0f, 0.0f), pitch - Math::kPiOver2);

	float	x = sinf(heading) * sinf(pitch) * range,
			y = cosf(pitch) * range,
			z = cosf(heading) * sinf(pitch) * range;

	m_Camera->SetPosition(Vector3f(x, y, z) + m_LookAtPos);
	m_Camera->SetRotation(quatHeading * quatPitch);
}

void RainGame::RenderScene()
{
	// 渲染场景
	// 使用当前摄像机作为渲染视点
	RenderView rv;

	rv.position = m_Camera->WorldTransform().GetPosition();
	rv.viewMatrix = m_Camera->GetViewMatrix();
	rv.projMatrix = m_Camera->GetProjMatrix();
	rv.frustum = m_Camera->GetFrustum();

	// 设定渲染视点
	m_Scene->SetupRenderView(rv);
	m_Scene->RenderScene(m_DebugRender);
}

Zone* RainGame::SelectZoneByClick(int mx, int my)
{
	int w = System::Instance().GetRenderWindowParameters()->width,
		h = System::Instance().GetRenderWindowParameters()->height;

	float	x = (float)mx / w,
			y = (float)my / h;

	// 从屏幕点击创建射线
	Ray ray = m_Camera->GetCameraRay(x, y);

	// 拾取场景对象
	ObjectsCollisionInfos info;
	m_Scene->RayPickingSceneObject(ray, info, 0);

	// 取消选择原有区域
	if (m_SelectedZone)
		m_SelectedZone->OnDeselected();

	// 检测是否选中任何新区域
	ObjectsCollisionInfos::iterator iter = info.begin();
	if (iter!=info.end())
	{
		m_SelectedZone = static_cast<Zone*>(iter->obj);
	}
	else
		m_SelectedZone = NULL;

	// 设置选择新区域
	if (m_SelectedZone)
		m_SelectedZone->OnSelected();
	
	return m_SelectedZone;
}

#ifdef RAIN_EDITOR
void RainGame::SlotTest()
{
	int w = 0;
}
#endif
